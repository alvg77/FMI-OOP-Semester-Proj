#include "Maze.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <boost/format.hpp>
#include <ostream>

#include "CellState.hpp"

Maze::Maze(const unsigned rows, const unsigned cols)
    : rows(rows), cols(cols), grid(rows, std::vector<unsigned>(cols, WALL)) {}

void Maze::setPath(const unsigned row, const unsigned col) {
  grid[row][col] = PATH;
}

bool Maze::isWall(const unsigned row, const unsigned col) const {
  return grid[row][col] == WALL;
}

std::vector<std::pair<unsigned, unsigned>> Maze::getNeighbours(
    const unsigned row, const unsigned col) const {
  constexpr int directionRows[4] = {-2, 2, 0, 0};
  constexpr int directionCols[4] = {0, 0, -2, 2};

  std::vector<std::pair<unsigned, unsigned>> neighbours;

  for (int i = 0; i < 4; ++i) {
    int nr = static_cast<int>(row) + directionRows[i];
    int nc = static_cast<int>(col) + directionCols[i];

    if (nr > 0 && nr < static_cast<int>(rows) - 1 && nc > 0 &&
        nc < static_cast<int>(cols) - 1) {
      if (grid[nr][nc]) {
        neighbours.emplace_back(nr, nc);
      }
    }
  }

  return neighbours;
}

void Maze::display() const {
  using boost::format;

  std::cout << "   ";
  for (unsigned i = 0; i < cols; ++i) {
    std::cout << format("%2d ") % i;
  }
  std::cout << std::endl;

  for (unsigned i = 0; i < rows; ++i) {
    std::cout << format("%2d ") % i;
    for (unsigned j = 0; j < cols; ++j) {
      std::cout << " ";
      if (grid[i][j] == 0) {
        std::cout << ".";
      } else if (grid[i][j] == 1) {
        std::cout << "#";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

nlohmann::json Maze::toJson() const {
  using nlohmann::json;

  json jsonData;
  jsonData["rows"] = rows;
  jsonData["columns"] = cols;
  jsonData["grid"] = grid;

  return jsonData;
}

bool Maze::isWithinBounds(const unsigned row, const unsigned col) const {
  return row < rows && col < cols;
}
