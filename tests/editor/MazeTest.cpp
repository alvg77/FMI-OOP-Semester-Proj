#include <doctest/doctest.h>

#include "Maze/Maze.hpp"

TEST_CASE("Maze initialization") {
  const Maze maze(5, 5);

  for (unsigned r = 0; r < 5; ++r) {
    for (unsigned c = 0; c < 5; ++c) {
      CHECK(maze.isWall(r, c));
    }
  }
}

TEST_CASE("setPath and isWall") {
  Maze maze(3, 3);

  maze.setPath(1, 1);
  CHECK_FALSE(maze.isWall(1, 1));
  CHECK(maze.isWall(0, 0));
}

TEST_CASE("isWithinBounds works") {
  Maze maze(4, 4);

  CHECK(maze.isWithinBounds(0, 0));
  CHECK(maze.isWithinBounds(3, 3));
  CHECK_FALSE(maze.isWithinBounds(4, 0));
  CHECK_FALSE(maze.isWithinBounds(0, 4));
  CHECK_FALSE(maze.isWithinBounds(100, 100));
}

TEST_CASE("getNeighbours returns correct neighbors") {
  Maze maze(7, 7);

  auto neighbours = maze.getNeighbours(3, 3);

  std::vector<std::pair<unsigned,unsigned>> expected = {
    {1,3}, {5,3}, {3,1}, {3,5}
  };

  for (const auto& nbr : expected) {
    CHECK(std::find(neighbours.begin(), neighbours.end(), nbr) != neighbours.end());
  }

  CHECK_EQ(neighbours.size(), expected.size());

  maze.setPath(5, 3);
  neighbours = maze.getNeighbours(3, 3);

  CHECK(std::find(neighbours.begin(), neighbours.end(), std::make_pair(5u, 3u)) == neighbours.end());
}
