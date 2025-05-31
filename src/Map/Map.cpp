#include "Map.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <random>

#include "../Game/GameAction.hpp"
#include "Cell/Cell.hpp"

Map::Map(const unsigned rows, const unsigned cols, const unsigned finishRow, const unsigned finishCol,
         const unsigned playerRow, const unsigned playerCol,
         const std::vector<std::vector<Cell*>>& grid)
    : rows(rows),
      cols(cols),
      finishRow(finishRow),
      finishCol(finishCol),
      playerRow(playerRow),
      playerCol(playerCol),
      grid(grid) {}

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

nlohmann::json Map::toJson() const {
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

bool Map::isWithinBounds(const unsigned row, const unsigned col) const {
  return row < rows && col < cols;
}