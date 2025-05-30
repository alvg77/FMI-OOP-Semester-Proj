#include "MapFactory.hpp"

#include "../Entity/Creature/Monster/MonsterFactory.hpp"
#include "../Entity/Item/ItemFactory.hpp"
#include "../Entity/Wall/Wall.hpp"
#include "Cell/Cell.hpp"
#include "LevelLoader/LevelLoader.hpp"
#include "Map.hpp"

Map* MapFactory::createMap(const unsigned level) {
  return LevelLoader::load(level);
}

Map* MapFactory::createMapFromJson(const nlohmann::json& mapJson) {
  const unsigned cols = mapJson["columns"];
  const unsigned rows = mapJson["rows"];
  const unsigned playerRow = mapJson["playerRow"];
  const unsigned playerCol = mapJson["playerCol"];
  const unsigned finishRow = mapJson["finishRow"];
  const unsigned finishCol = mapJson["finishCol"];

  std::vector<std::vector<Cell*>> grid (rows, std::vector<Cell*>(cols, nullptr));
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
    const unsigned r = monsterJson["row"];
    const unsigned c = monsterJson["column"];

    grid[r][c]->addEntity(MonsterFactory::createMonsterFromJson(monsterJson));
  }

  const std::vector<json> treasuresJson = mapJson["treasures"];
  for (const json& treasureJson : treasuresJson) {
    const unsigned r = treasureJson["row"];
    const unsigned c = treasureJson["column"];

    grid[r][c]->addEntity(ItemFactory::createItemFromJson(treasureJson));
  }

  return new Map(rows, cols, finishRow, finishCol, playerRow, playerCol, grid);
}
