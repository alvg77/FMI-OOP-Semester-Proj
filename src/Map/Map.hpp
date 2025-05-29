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
  explicit Map(unsigned n);
  explicit Map(const nlohmann::json& mapJson);
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

  void loadLevel(unsigned n);
  void loadJson(const nlohmann::json& mapJson);

  bool isWithinBounds(unsigned row, unsigned col) const;
};

#endif  // MAP_HPP
