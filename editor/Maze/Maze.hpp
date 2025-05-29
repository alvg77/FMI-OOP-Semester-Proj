#ifndef GRID_HPP
#define GRID_HPP

#include <nlohmann/json_fwd.hpp>
#include <vector>

class Maze {
 public:
  Maze(unsigned rows, unsigned cols);

  void setPath(unsigned row, unsigned col);
  bool isWall(unsigned row, unsigned col) const;
  std::vector<std::pair<unsigned, unsigned>> getNeighbours(unsigned row,
                                                           unsigned col) const;
  void display() const;

  nlohmann::json toJson() const;

  bool isWithinBounds(unsigned row, unsigned col) const;

 private:
  unsigned rows;
  unsigned cols;
  std::vector<std::vector<unsigned>> grid;
};

#endif  // GRID_HPP
