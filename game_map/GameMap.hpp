//
// Created by Alek on 5/17/2025.
//

#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

class Item;

class GameMap {
 public:
  GameMap();
  GameMap(const GameMap& other);
  GameMap& operator=(const GameMap& other);
  ~GameMap();

  void loadNextMap();
  void displayMap() const;

  friend void swap(GameMap& a, GameMap& b) noexcept;

 private:
  unsigned width, height;
  unsigned monsters;
  unsigned treasures;
  char** currentMap;
  unsigned currentLevel;
  std::vector<Item*> treasurePool;
  static const std::string levelFileLocation;

  void placeOnMapRandom(const std::vector<std::pair<unsigned, unsigned>>& freeSpaces, char c, unsigned amountToBePlaced) const;
};

void swap(GameMap& a, GameMap& b) noexcept;

#endif  // MAP_HPP
