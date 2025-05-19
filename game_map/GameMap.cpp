#include "GameMap.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "../item/Item.hpp"
#include "nlohmann/json.hpp"

const std::string GameMap::levelFileLocation = "../resources/level_maps/";

GameMap::GameMap()
    : width(0),
      height(0),
      monsters(0),
      treasures(0),
      currentLevel(1),
      currentMap(nullptr),
      playerX(0),
      playerY(0) {
  loadNextMap();
}

GameMap::GameMap(const GameMap& other)
    : width(other.width),
      height(other.height),
      monsters(other.monsters),
      treasures(other.treasures),
      currentLevel(other.currentLevel),
      playerX(other.playerX),
      playerY(other.playerY) {
  currentMap = new char*[height];
  for (unsigned i = 0; i < height; ++i) {
    currentMap[i] = new char[width];
  }

  for (unsigned i = 0; i < height; ++i) {
    for (unsigned j = 0; j < width; ++j) {
      currentMap[i][j] = other.currentMap[i][j];
    }
  }
}

GameMap& GameMap::operator=(const GameMap& other) {
  if (this != &other) {
    GameMap temp(other);
    swap(*this, temp);
  }

  return *this;
}

GameMap::~GameMap() {
  for (const Item* itemPtr : treasurePool) {
    delete itemPtr;
  }

  for (unsigned i = 0; i < height; ++i) {
    delete[] currentMap[i];
  }
  delete currentMap;
}

void GameMap::loadNextMap() {
  using nlohmann::json;

  std::ifstream jsonFileStream(GameMap::levelFileLocation + "level" +
                               std::to_string(currentLevel++) + ".json");

  json jsonData = json::parse(jsonFileStream);

  if (!jsonData.contains("width") || !jsonData.contains("height") ||
      !jsonData.contains("treasure_pool") || !jsonData.contains("grid") ||
      !jsonData.contains("monsters") || !jsonData.contains("treasures")) {
    throw std::invalid_argument("Invalid format of level map file!");
  }

  width = jsonData["width"].get<unsigned>();
  height = jsonData["height"].get<unsigned>();

  monsters = jsonData["monsters"].get<unsigned>();
  treasures = jsonData["treasures"].get<unsigned>();

  for (json::const_iterator it = jsonData["treasure_pool"].cbegin();
       it != jsonData["treasure_pool"].cend(); ++it) {
    const json& treasure = *it;

    if (!treasure.contains("name") || !treasure.contains("bonus") ||
        !treasure.contains("type")) {
      throw std::invalid_argument("Invalid treasure in treasure list!");
    }

    std::string name = treasure["name"].get<std::string>();
    const unsigned bonus = treasure["bonus"].get<unsigned>();
    const ItemType itemType = toItemType(treasure["type"].get<std::string>());

    Item* item = new Item(name, bonus, itemType);
    treasurePool.push_back(item);
  }

  std::vector<std::pair<unsigned, unsigned>> freeSpaces;
  currentMap = new char*[height];
  unsigned row = 0;

  if (!jsonData["grid"].is_array()) {
    throw std::invalid_argument("Invalid type used for grid!");
  }

  if (jsonData["grid"].size() != height) {
    throw std::invalid_argument("Grid height is incorrect!");
  }

  for (json::const_iterator it = jsonData["grid"].cbegin();
       it < jsonData["grid"].cend(); ++it) {
    currentMap[row] = new char[width];
    unsigned col = 0;

    if (!it->is_array()) {
      throw std::invalid_argument("Invalid inner grid!");
    }

    if (it->size() != width) {
      throw std::invalid_argument("Invalid grid width!");
    }

    for (json::const_iterator inner = it->cbegin(); inner < it->cend();
         ++inner) {
      switch (inner->get<unsigned>()) {
        case 0:
          currentMap[row][col] = '.';
          freeSpaces.emplace_back(row, col);
          break;
        case 1:
          currentMap[row][col] = '#';
          break;
        default:
          throw std::invalid_argument("Invalid grid element!");
      }
      ++col;
    }
    ++row;
  }

  playerX = freeSpaces.begin()->first;
  playerY = freeSpaces.begin()->second;
  freeSpaces.erase(freeSpaces.begin());

  placeEntitiesOnMapRandom(freeSpaces, 'M', monsters);
  placeEntitiesOnMapRandom(freeSpaces, 'T', treasures);
}

void GameMap::displayMap() const {
  for (unsigned i = 0; i < height; ++i) {
    for (unsigned j = 0; j < width; ++j) {
      if (playerX == j && playerY == i) {
        std::cout << " P ";
      } else {
        std::cout << " " << currentMap[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }

  std::cout << "\n---LEVEL STATS---" << std::endl;
  std::cout << "Monsters: " << monsters << std::endl;
  std::cout << "Treasures: " << treasures << std::endl;

  std::cout << "\n---TREASURE POOL---" << std::endl;
  for (const Item* itemPtr : treasurePool) {
    std::cout << *itemPtr << std::endl;
  }
}

bool GameMap::movePlayer(const MoveDirection direction) {
  switch (direction) {
    case MoveDirection::UP:
      if (static_cast<long>(playerY - 1) >= 0 &&
          canMoveThere(playerX, playerY - 1)) {
        playerY -= 1;
        return true;
      }
      return false;
    case MoveDirection::DOWN:
      if (playerY + 1 < height && canMoveThere(playerX, playerY + 1)) {
        playerY += 1;
        return true;
      }
      return false;
    case MoveDirection::LEFT:
      if (static_cast<long>(playerX - 1) >= 0 &&
          canMoveThere(playerX - 1, playerY)) {
        playerX -= 1;
        return true;
      }
      return false;
    case MoveDirection::RIGHT:
      if (playerX + 1 < width && canMoveThere(playerX + 1, playerY)) {
        playerX += 1;
        return true;
      }
      return false;
    default:
      throw std::invalid_argument("Invalid movement direction!");
  }
}

bool GameMap::startFight() const { return currentMap[playerY][playerX] == 'M'; }

bool GameMap::lootTreasure() const {
  return currentMap[playerY][playerX] == 'T';
}

void GameMap::placeEntitiesOnMapRandom(
    const std::vector<std::pair<unsigned, unsigned>>& freeSpaces, char c,
    const unsigned amountToBePlaced) {
  const unsigned int seed = time(nullptr);
  std::mt19937 rng(seed);

  std::uniform_int_distribution<unsigned> unif(0, freeSpaces.size() - 1);

  for (unsigned i = 0; i < amountToBePlaced; ++i) {
    unsigned idx = 0;
    unsigned row = 0, col = 0;
    do {
      idx = unif(rng);
      row = freeSpaces.at(idx).first;
      col = freeSpaces.at(idx).second;
    } while (currentMap[row][col] != '.');
    currentMap[freeSpaces.at(idx).first][freeSpaces.at(idx).second] = c;
  }
}

bool GameMap::canMoveThere(unsigned x, unsigned y) const {
  return currentMap[y][x] != '#';
}

void swap(GameMap& a, GameMap& b) noexcept {
  using std::swap;

  swap(a.width, b.width);
  swap(a.height, b.height);
  swap(a.currentMap, b.currentMap);
}
