#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

class Cell;
class Item;
class NPEntity;
class Hero;

enum class MoveDirection { UP, DOWN, LEFT, RIGHT };

class Map {
 public:
  explicit Map(unsigned n);
  Map(const Map& other) = delete;
  Map& operator=(const Map& other) = delete;
  ~Map();

  bool moveHero(Hero& hero, MoveDirection direction);

  bool hasReachedEnd() const;

  void display(std::ostream& os = std::cout) const;

 private:
  unsigned rows, cols;
  std::vector<std::vector<Cell*>> grid;
  unsigned monsters, treasures;
  unsigned finishRow, finishCol;
  unsigned playerRow, playerCol;

  void loadLevel(unsigned n);
  void placeEntityAtRandom(
      NPEntity* entity,
      std::vector<std::pair<unsigned, unsigned>>& freeCells);

  bool isWithinBounds(unsigned row, unsigned col) const;

  static const std::string levelFileLocation;
  static const std::string monstersFileLocation;
};

#endif  // MAP_HPP
