#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include "MoveDirection.hpp"

class Item;

class GameMap {
 public:
  GameMap();
  GameMap(const GameMap& other);
  GameMap& operator=(const GameMap& other);
  ~GameMap();

  void loadNextMap();
  void displayMap() const;
  bool movePlayer(MoveDirection direction);
  bool startFight() const;
  bool lootTreasure() const;

  friend void swap(GameMap& a, GameMap& b) noexcept;

 private:
  unsigned width, height;
  unsigned monsters;
  unsigned treasures;
  unsigned currentLevel;
  std::vector<Item*> treasurePool;
  char** currentMap;

  unsigned playerX, playerY;

  static const std::string levelFileLocation;

  void placeEntitiesOnMapRandom(
      const std::vector<std::pair<unsigned, unsigned>>& freeSpaces, char c,
      unsigned amountToBePlaced);

  bool canMoveThere(unsigned x, unsigned y) const;
};

void swap(GameMap& a, GameMap& b) noexcept;

#endif  // MAP_HPP
