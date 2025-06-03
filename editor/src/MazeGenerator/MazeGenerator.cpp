#include "MazeGenerator.hpp"

#include <__random/random_device.h>

#include <random>
#include <stack>

#include "../Maze/Maze.hpp"

Maze MazeGenerator::generate(const unsigned rows, const unsigned cols) {
  Maze maze(rows, cols);

  std::random_device rd;
  std::mt19937 rng(rd());

  std::stack<std::pair<unsigned, unsigned>> stack;
  std::pair<unsigned, unsigned> start = {1, 1};
  maze.setPath(start.first, start.second);
  stack.emplace(start);


  while (!stack.empty()) {
    std::pair<unsigned, unsigned> current = stack.top();
    std::vector<std::pair<unsigned, unsigned>> neighbours = maze.getNeighbours(current.first, current.second);

    if (!neighbours.empty()) {
      std::shuffle(neighbours.begin(), neighbours.end(), rng);
      std::pair<unsigned, unsigned> next = neighbours[0];

      const int wallRow = static_cast<int>(current.first + next.first) / 2;
      const int wallCol = static_cast<int>(current.second + next.second) / 2;

      maze.setPath(wallRow, wallCol);
      maze.setPath(next.first, next.second);

      stack.push(next);
    } else {
      stack.pop();
    }
  }

  return maze;
}