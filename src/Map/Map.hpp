#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <random>
#include <vector>

enum class GameAction;
struct LoadedLevel;
class Cell;
class Item;
class NPEntity;
class Hero;

class Map {
 public:
  Map(unsigned rows, unsigned cols, unsigned finishRow, unsigned finishCol,
      unsigned playerRow, unsigned playerCol,
      const std::vector<std::vector<Cell*>>& grid);
  Map(const Map& other) = delete;
  Map& operator=(const Map& other) = delete;
  ~Map();

  bool moveHero(Hero& hero, GameAction direction);

  bool hasReachedEnd() const;

  void display(std::ostream& os = std::cout) const;

  nlohmann::json toJson() const;

 private:
  unsigned rows, cols;
  unsigned finishRow, finishCol;
  unsigned playerRow, playerCol;
  std::vector<std::vector<Cell*>> grid;

  std::mt19937 rng = std::mt19937(std::random_device{}());

  bool isWithinBounds(unsigned row, unsigned col) const;
};

#endif  // MAP_HPP
