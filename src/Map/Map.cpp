#include "Map.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <random>

#include "../Entity/Creature/Monster/Monster.hpp"
#include "../Entity/Item/Item.hpp"
#include "../Entity/Wall/Wall.hpp"
#include "../Game/GameAction.hpp"
#include "Cell/Cell.hpp"
#include "LevelLoader/LevelLoader.hpp"
#include "LevelLoader/LoadedLevel.hpp"

Map::Map(const unsigned n)
    : rows(0),
      cols(0),
      finishRow(0),
      finishCol(0),
      playerRow(0),
      playerCol(0) {
  loadLevel(n);
}

Map::Map(const nlohmann::json& mapJson)
    : rows(0),
      cols(0),
      finishRow(0),
      finishCol(0),
      playerRow(0),
      playerCol(0) {
  loadJson(mapJson);
}

Map::~Map() {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      delete grid[i][j];
    }
  }
}

bool Map::moveHero(Hero& hero, GameAction direction) {
  switch (direction) {
    case GameAction::MOVE_UP:
      if (isWithinBounds(playerRow - 1, playerCol) &&
          grid[playerRow - 1][playerCol]->step(hero)) {
        playerRow -= 1;
        grid[playerRow][playerCol]->interact(hero);
        return true;
      }
      return false;
    case GameAction::MOVE_DOWN:
      if (isWithinBounds(playerRow + 1, playerCol) &&
          grid[playerRow + 1][playerCol]->step(hero)) {
        playerRow += 1;
        grid[playerRow][playerCol]->interact(hero);
        return true;
      }
      return false;
    case GameAction::MOVE_LEFT:
      if (isWithinBounds(playerRow, playerCol - 1) &&
          grid[playerRow][playerCol - 1]->step(hero)) {
        playerCol -= 1;
        grid[playerRow][playerCol]->interact(hero);
        return true;
      }
      return false;
    case GameAction::MOVE_RIGHT:
      if (isWithinBounds(playerRow, playerCol + 1) &&
          grid[playerRow][playerCol + 1]->step(hero)) {
        playerCol += 1;
        grid[playerRow][playerCol]->interact(hero);
        return true;
      }
      return false;
    default:
      return false;
  }
}

bool Map::hasReachedEnd() const {
  return playerRow == finishRow && playerCol == finishCol;
}

void Map::display(std::ostream& os) const {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      if (i == playerRow && j == playerCol) {
        os << " P ";
      } else if (i == finishRow && j == finishCol) {
        os << " F ";
      } else {
        os << " " << grid[i][j]->getSymbol() << " ";
      }
    }
    os << std::endl;
  }
}

void Map::loadLevel(const unsigned n) {
  LoadedLevel level = LevelLoader::load(n);

  rows = level.rows;
  cols = level.cols;
  playerRow = level.playerRow;
  playerCol = level.playerCol;
  finishRow = level.finishRow;
  finishCol = level.finishCol;
  grid = std::move(level.grid);
}

json Map::toJson() const {
  using nlohmann::json;

  json mapJson;

  mapJson["rows"] = rows;
  mapJson["columns"] = cols;
  mapJson["finishRow"] = finishRow;
  mapJson["finishCol"] = finishCol;
  mapJson["playerRow"] = playerRow;
  mapJson["playerCol"] = playerCol;

  std::vector<json> monstersJson;
  std::vector<json> treasuresJson;
  std::vector<std::vector<unsigned short>> mapGrid(
      rows, std::vector<unsigned short>(cols, 0));

  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      if (grid[i][j] != nullptr) {
        switch (grid[i][j]->getSymbol()) {
          case '#':
            mapGrid[i][j] = 1;
            break;
          case '.':
            break;
          case 'M': {
            json monsterJson = grid[i][j]->getEntityJson();
            monsterJson["row"] = i;
            monsterJson["column"] = j;
            monstersJson.push_back(monsterJson);
            mapGrid[i][j] = 0;
            break;
          }
          case 'T': {
            json itemJson = grid[i][j]->getEntityJson();
            itemJson["row"] = i;
            itemJson["column"] = j;
            treasuresJson.push_back(itemJson);
            mapGrid[i][j] = 0;
            break;
          }
          default:
            throw std::runtime_error("Unknown grid marker encountered!");
        }
      }
    }
  }

  mapJson["monsters"] = monstersJson;
  mapJson["treasures"] = treasuresJson;

  mapJson["grid"] = mapGrid;

  return mapJson;
}

void Map::loadJson(const json& mapJson) {
  cols = mapJson["columns"];
  rows = mapJson["rows"];
  playerRow = mapJson["playerRow"];
  playerCol = mapJson["playerCol"];
  finishRow = mapJson["finishRow"];
  finishCol = mapJson["finishCol"];

  grid.resize(rows, std::vector<Cell*>(cols, nullptr));
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
  for (const json& monsterData : monstersJson) {
    const unsigned r = monsterData["row"];
    const unsigned c = monsterData["column"];

    grid[r][c]->addEntity(new Monster(monsterData));
  }

  const std::vector<json> treasuresJson = mapJson["treasures"];
  for (const json& treasureData : treasuresJson) {
    const unsigned r = treasureData["row"];
    const unsigned c = treasureData["column"];

    grid[r][c]->addEntity(new Item(treasureData));
  }
}

bool Map::isWithinBounds(const unsigned row, const unsigned col) const {
  return row < rows && col < cols;
}