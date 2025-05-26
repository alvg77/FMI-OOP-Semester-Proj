#include "LevelLoader.hpp"

#include <iostream>
#include <fstream>
#include <random>

#include "../../Entity/Creature/Monster/Monster.hpp"
#include "../../Entity/Creature/Stats.hpp"
#include "../../Entity/Item/Item.hpp"
#include "../../Entity/Wall/Wall.hpp"
#include "../Cell/Cell.hpp"

LevelLoader::LoadedLevel LevelLoader::load(const std::string& path,
                                           const std::string& monstersPath) {
  json data = readJson(path);
  validateLevelJson(data);

  LoadedLevel level;
  level.monsterN = data["monsterN"].get<unsigned>();
  level.treasureN = data["treasureN"].get<unsigned>();
  level.rows = data["rows"].get<unsigned>();
  level.cols = data["columns"].get<unsigned>();

  parseGrid(data["grid"], level.grid, level.freeSpaces, level.cols);

  if (!data.contains("treasure_pool") || !data["treasure_pool"].is_array()) {
    throw std::invalid_argument("Invalid or missing treasure_pool.");
  }
  level.items = loadItems(data["treasure_pool"], level.treasureN);

  level.monsters = loadMonsters(monstersPath, level.monsterN);

  return level;
}

void LevelLoader::validateLevelJson(const json& data) {
  const std::vector<std::string> requiredFields = {
      "columns",  "rows",     "treasure_pool", "grid",
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

json LevelLoader::readJson(const std::string& path) {
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
    const json& jsonGrid, std::vector<std::vector<Cell*>>& grid,
    std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
    const unsigned cols) {
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
      unsigned val = rowJson[col].get<unsigned>();
      switch (val) {
        case 0:
          grid[row][col] = new Cell();
          freeSpaces.emplace_back(row, col);
          break;
        case 1: {
          Wall* wall = new Wall();
          grid[row][col] = new Cell(wall);
          delete wall;
          break;
        }
        default:
          throw std::invalid_argument("Unknown cell type in grid: " +
                                      std::to_string(val));
      }
    }
  }
}

std::vector<Item*> LevelLoader::loadItems(const json& treasurePool,
                                          const unsigned n) {
  if (treasurePool.size() < n) {
    throw std::invalid_argument(
        "Not enough treasures in the pool to choose from.");
  }

  std::vector<json> pool = treasurePool.get<std::vector<json>>();
  std::shuffle(pool.begin(), pool.end(), std::mt19937{std::random_device{}()});

  std::vector<Item*> items;
  for (unsigned i = 0; i < n; ++i) {
    const json& itemJson = pool[i];
    std::string name = itemJson["name"].get<std::string>();
    const double bonus = itemJson["bonus"].get<double>();
    std::string typeStr = itemJson["type"].get<std::string>();

    Item* item = new Item(name, bonus, getItemType(typeStr));
    items.push_back(item);
  }

  return items;
}

std::vector<Monster*> LevelLoader::loadMonsters(const std::string& path,
                                                const unsigned count) {
  json data = readJson(path);

  if (!data.contains("monsters") || !data["monsters"].is_array()) {
    throw std::invalid_argument("Invalid monsters JSON format.");
  }

  std::vector<json> monsterList = data["monsters"].get<std::vector<json>>();
  if (monsterList.size() < count) {
    throw std::invalid_argument("Not enough monsters in the pool to select.");
  }

  std::shuffle(monsterList.begin(), monsterList.end(),
               std::mt19937{std::random_device{}()});

  std::vector<Monster*> monsters;
  for (unsigned i = 0; i < count; ++i) {
    const json& monsterJson = monsterList[i];

    std::string name = monsterJson["name"].get<std::string>();
    unsigned level = monsterJson["level"].get<unsigned>();

    Stats stats{};
    stats.strength = monsterJson["stats"]["strength"].get<unsigned>();
    stats.mana = monsterJson["stats"]["mana"].get<unsigned>();
    stats.maxHealth = monsterJson["stats"]["maxHealth"].get<unsigned>();

    Monster* monster = new Monster(name, level, stats);
    monsters.push_back(monster);
  }

  return monsters;
}