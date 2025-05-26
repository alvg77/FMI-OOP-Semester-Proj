#include "Map.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <random>

#include "../Entity/Creature/Monster/Monster.hpp"
#include "../Entity/Item/Item.hpp"
#include "../Entity/Wall/Wall.hpp"
#include "Cell/Cell.hpp"
#include "LevelLoader/LevelLoader.hpp"

const std::string Map::levelFileLocation = "../data/levels/";
const std::string Map::monstersFileLocation = "../data/monsters/monsters.json";

Map::Map(const unsigned n)
    : rows(0),
      cols(0),
      monsters(0),
      treasures(0),
      finishRow(0),
      finishCol(0),
      playerRow(0),
      playerCol(0) {
  loadLevel(n);
}

Map::~Map() {
  for (unsigned i = 0; i < cols; ++i) {
    for (unsigned j = 0; j < rows; ++j) {
      delete grid[i][j];
    }
  }
}

bool Map::moveHero(Hero& hero, MoveDirection direction) {
  switch (direction) {
    case MoveDirection::UP:
      if (isWithinBounds(playerRow, playerCol - 1) &&
          grid[playerCol - 1][playerRow]->step(hero)) {
        playerCol -= 1;
        grid[playerCol][playerRow]->interact(hero);
        return true;
      }
      return false;
    case MoveDirection::DOWN:
      if (isWithinBounds(playerRow, playerCol + 1) &&
          grid[playerCol + 1][playerRow]->step(hero)) {
        playerCol += 1;
        grid[playerCol][playerRow]->interact(hero);
        return true;
      }
      return false;
    case MoveDirection::LEFT:
      if (isWithinBounds(playerRow - 1, playerCol) &&
          grid[playerCol][playerRow - 1]->step(hero)) {
        playerRow -= 1;
        grid[playerCol][playerRow]->interact(hero);
        return true;
      }
      return false;
    case MoveDirection::RIGHT:
      if (isWithinBounds(playerRow + 1, playerCol) &&
          grid[playerCol][playerRow + 1]->step(hero)) {
        grid[playerCol][playerRow]->interact(hero);
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
  for (unsigned i = 0; i < cols; ++i) {
    for (unsigned j = 0; j < rows; ++j) {
      if (j == playerRow && i == playerCol) {
        os << " P ";
      } else {
        os << " " << grid[i][j]->getSymbol() << " ";
      }
    }
    os << std::endl;
  }
}

void Map::loadLevel(unsigned n) {
  const std::string levelPath =
      Map::levelFileLocation + "level" + std::to_string(n) + ".json";

  LevelLoader::LoadedLevel level =
      LevelLoader::load(levelPath, monstersFileLocation);

  monsters = level.monsterN;
  treasures = level.treasureN;
  rows = level.rows;
  cols = level.cols;
  grid = std::move(level.grid);

  for (Item* item : level.items) {
    placeEntityAtRandom(item, level.freeSpaces);
    delete item;
  }

  for (Monster* monster : level.monsters) {
    placeEntityAtRandom(monster, level.freeSpaces);
    delete monster;
  }

  if (level.freeSpaces.size() < 2) {
    throw std::runtime_error(
        "Not enough free spaces to place player and finish.");
  }

  playerRow = level.freeSpaces.front().first;
  playerCol = level.freeSpaces.front().second;
  level.freeSpaces.erase(level.freeSpaces.begin());

  finishRow = level.freeSpaces.back().first;
  finishCol = level.freeSpaces.back().second;
  level.freeSpaces.pop_back();
}

void Map::placeEntityAtRandom(
    NPEntity* entity,
    std::vector<std::pair<unsigned, unsigned>>& freeCells) {
  const unsigned int seed = time(nullptr);
  std::mt19937 rng(seed);
  std::uniform_int_distribution<unsigned> unif(0, freeCells.size() - 1);

  const unsigned idx = unif(rng);

  grid[freeCells[idx].first][freeCells[idx].second]->addEntity(entity);

  freeCells.erase(freeCells.begin() + idx);
}

bool Map::isWithinBounds(const unsigned row, const unsigned col) const {
  return row < rows && col < cols;
}
