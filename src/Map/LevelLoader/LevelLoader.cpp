#include "LevelLoader.hpp"

#include <fstream>
#include <random>

#include "../../Entity/Creature/Monster/Monster.hpp"
#include "../../Entity/Creature/Monster/MonsterFactory.hpp"
#include "../../Entity/Creature/Stats.hpp"
#include "../../Entity/Item/Item.hpp"
#include "../../Entity/Wall/Wall.hpp"
#include "../Cell/Cell.hpp"
#include "../LoadedLevel.hpp"
#include "../Map.hpp"

std::mt19937 LevelLoader::rng = std::mt19937(std::random_device{}());
const std::string LevelLoader::levelFileLocation = "../data/levels/level";
const std::string LevelLoader::monstersFileLocation =
    "../data/monsters/monsters";
const std::string LevelLoader::itemsFileLocation = "../data/items/items";

Map* LevelLoader::load(const unsigned n) {
  using nlohmann::json;

  const std::string levelPath =
      LevelLoader::levelFileLocation + std::to_string(n) + ".json";

  json data = readJson(levelPath);
  validateLevelJson(data);

  LoadedLevel level;
  const unsigned monsterN = data["monsterN"].get<unsigned>();
  const unsigned treasureN = data["treasureN"].get<unsigned>();
  level.rows = data["rows"].get<unsigned>();
  level.cols = data["columns"].get<unsigned>();
  level.finishRow = data["finishRow"];
  level.finishCol = data["finishCol"];

  std::vector<std::pair<unsigned, unsigned>> freeSpaces;

  parseGrid(data["grid"], level.grid, freeSpaces, level.cols);

  const auto it = std::find(freeSpaces.begin(), freeSpaces.end(),
                      std::pair<unsigned, unsigned>(level.finishRow, level.finishCol));
  if (it != freeSpaces.end()) {
    freeSpaces.erase(it);
  } else {
    throw std::runtime_error("Finish cell should be free!");
  }

  level.playerRow = freeSpaces.begin()->first;
  level.playerCol = freeSpaces.begin()->second;
  freeSpaces.erase(freeSpaces.begin());

  std::vector<NPEntity*> items = loadItems(treasureN, n);
  placeEntitiesAtRandomAndClear(items, freeSpaces, level.grid);

  std::vector<NPEntity*> monsters = loadMonsters(monsterN, n);
  placeEntitiesAtRandomAndClear(monsters, freeSpaces, level.grid);

  return new Map(level.rows, level.cols, level.finishRow, level.finishCol, level.playerRow, level.playerCol, level.grid);
}

void LevelLoader::validateLevelJson(const nlohmann::json& data) {
  const std::vector<std::string> requiredFields = {"columns", "rows", "grid",
                                                   "monsterN", "treasureN"};

  for (const std::string& field : requiredFields) {
    if (!data.contains(field)) {
      throw std::invalid_argument("Missing required field in level JSON: " +
                                  field);
    }
  }

  if (!data["grid"].is_array() || data["grid"].size() != data["rows"]) {
    throw std::invalid_argument(
        "Grid must be an array of rows matching 'rows' count.");
  }
}

nlohmann::json LevelLoader::readJson(const std::string& path) {
  using nlohmann::json;

  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open JSON file: " + path);
  }

  json data;
  file >> data;
  file.close();
  return data;
}

void LevelLoader::parseGrid(
    const nlohmann::json& jsonGrid, std::vector<std::vector<Cell*>>& grid,
    std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
    const unsigned cols) {
  using nlohmann::json;

  const unsigned rows = jsonGrid.size();
  grid.resize(rows);

  for (unsigned row = 0; row < rows; ++row) {
    const json& rowJson = jsonGrid[row];
    if (!rowJson.is_array() || rowJson.size() != cols) {
      throw std::invalid_argument(
          "Each grid row must be an array of size equal to 'columns'.");
    }

    grid[row].resize(cols);

    for (unsigned col = 0; col < cols; ++col) {
      const unsigned val = rowJson[col].get<unsigned>();
      switch (val) {
        case 0:
          grid[row][col] = new Cell();
          freeSpaces.emplace_back(row, col);
          break;
        case 1:
          grid[row][col] = new Cell(new Wall());
          break;
        default:
          throw std::invalid_argument("Unknown cell type in grid: " +
                                      std::to_string(val));
      }
    }
  }
}

std::vector<NPEntity*> LevelLoader::loadItems(const unsigned count,
                                              const unsigned n) {
  using nlohmann::json;

  json data = readJson(itemsFileLocation + std::to_string(n) + ".json");

  if (!data.contains("items")) {
    throw std::runtime_error("Invalid item file.");
  }

  if (data["items"].size() < count) {
    throw std::runtime_error(
        "Not enough treasures in the pool to choose from.");
  }

  std::vector<json> pool = data["items"].get<std::vector<json>>();
  std::shuffle(pool.begin(), pool.end(), std::mt19937{std::random_device{}()});

  std::vector<NPEntity*> items;
  for (unsigned i = 0; i < count; ++i) {
    const json& itemJson = pool[i];
    std::string name = itemJson["name"].get<std::string>();
    const double bonus = itemJson["bonus"].get<double>();
    std::string typeStr = itemJson["type"].get<std::string>();

    Item* item = new Item(name, bonus, getItemType(typeStr));
    items.push_back(item);
  }

  return items;
}

std::vector<NPEntity*> LevelLoader::loadMonsters(const unsigned count,
                                                 const unsigned n) {
  using nlohmann::json;

  json data =
      readJson(LevelLoader::monstersFileLocation + std::to_string(n) + ".json");

  if (!data.contains("monsters") || !data["monsters"].is_array()) {
    throw std::invalid_argument("Invalid monsters JSON format.");
  }

  std::vector<json> monsterList = data["monsters"].get<std::vector<json>>();
  if (monsterList.size() < count) {
    throw std::invalid_argument("Not enough monsters in the pool to select.");
  }

  std::shuffle(monsterList.begin(), monsterList.end(),
               std::mt19937{std::random_device{}()});

  std::vector<NPEntity*> monsters;
  for (unsigned i = 0; i < count; ++i) {
    const json& monsterJson = monsterList[i];

    std::string name = monsterJson["name"].get<std::string>();
    const unsigned level = n;

    Stats stats{};
    stats.strength = monsterJson["stats"]["strength"].get<unsigned>();
    stats.mana = monsterJson["stats"]["mana"].get<unsigned>();
    stats.maxHealth = monsterJson["stats"]["maxhealth"].get<unsigned>();

    Monster* monster = MonsterFactory::createMonster(name, level, stats);
    monsters.push_back(monster);
  }

  return monsters;
}

void LevelLoader::placeEntitiesAtRandomAndClear(
    std::vector<NPEntity*>& entities,
    std::vector<std::pair<unsigned, unsigned>>& freeCells,
    const std::vector<std::vector<Cell*>>& grid) {
  for (NPEntity* entity : entities) {
    std::uniform_int_distribution<unsigned> unif(0, freeCells.size() - 1);
    const unsigned idx = unif(LevelLoader::rng);
    grid[freeCells[idx].first][freeCells[idx].second]->addEntity(entity);
    freeCells.erase(freeCells.begin() + idx);
  }
  entities.clear();
}
