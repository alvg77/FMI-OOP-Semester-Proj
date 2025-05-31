#include "MapFactory.hpp"

#include "../NPEntity/Item/ItemFactory.hpp"
#include "../NPEntity/Monster/MonsterFactory.hpp"
#include "../NPEntity/Wall/Wall.hpp"
#include "Cell/Cell.hpp"
#include "LevelLoader/LevelLoader.hpp"
#include "Map.hpp"

Map* MapFactory:: createMap(const unsigned level) {
  return LevelLoader::load(level);
}

Map* MapFactory::createMapFromJson(const nlohmann::json& mapJson) {
  using nlohmann::json;

  const unsigned cols = mapJson["columns"].get<unsigned>();
  const unsigned rows = mapJson["rows"].get<unsigned>();
  const unsigned playerRow = mapJson["playerRow"].get<unsigned>();
  const unsigned playerCol = mapJson["playerCol"].get<unsigned>();
  const unsigned finishRow = mapJson["finishRow"].get<unsigned>();
  const unsigned finishCol = mapJson["finishCol"].get<unsigned>();

  std::vector<std::vector<Cell*>> grid(rows, std::vector<Cell*>(cols, nullptr));
  const std::vector<json> gridData = mapJson["grid"];
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      if (gridData[i][j] == 1) {
        grid[i][j] = new Cell(new Wall());
      } else {
        grid[i][j] = new Cell();
      }
    }
  }

  const std::vector<json> monstersJson = mapJson["monsters"];
  for (const json& monsterJson : monstersJson) {
    const unsigned r = monsterJson["row"].get<unsigned>();
    const unsigned c = monsterJson["column"].get<unsigned>();

    if (r >= rows || c >= cols) {
      throw std::runtime_error(
          "Monster coordinates out of bounds! Invalid map JSON!");
    }

    grid[r][c]->addEntity(MonsterFactory::createMonsterFromJson(monsterJson));
  }

  const std::vector<json> treasuresJson = mapJson["treasures"];
  for (const json& treasureJson : treasuresJson) {
    const unsigned r = treasureJson["row"].get<unsigned>();
    const unsigned c = treasureJson["column"].get<unsigned>();

    if (r >= rows || c >= cols) {
      throw std::runtime_error(
          "Item coordinates out of bounds! Invalid map JSON!");
    }

    grid[r][c]->addEntity(ItemFactory::createItemFromJson(treasureJson));
  }

  return new Map(rows, cols, finishRow, finishCol, playerRow, playerCol, grid);
}
