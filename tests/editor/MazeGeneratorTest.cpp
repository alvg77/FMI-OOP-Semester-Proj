#include <doctest/doctest.h>
#include <nlohmann/json.hpp>

#include "Maze/Maze.hpp"
#include "MazeGenerator/MazeGenerator.hpp"

TEST_CASE("MazeGenerator produces maze of correct size") {
  const Maze maze = MazeGenerator::generate(7, 7);

  CHECK_EQ(maze.toJson()["rows"], 7);
  CHECK_EQ(maze.toJson()["columns"], 7);
}

TEST_CASE("MazeGenerator sets start cell as path") {
  const Maze maze = MazeGenerator::generate(7, 7);

  CHECK_FALSE(maze.isWall(1, 1));
}

TEST_CASE("MazeGenerator produces some paths and some walls") {
  const Maze maze = MazeGenerator::generate(7, 7);

  bool hasPath = false;
  bool hasWall = false;

  for (unsigned r = 0; r < 7; ++r) {
    for (unsigned c = 0; c < 7; ++c) {
      if (maze.isWall(r, c))
        hasWall = true;
      else
        hasPath = true;
    }
  }

  CHECK(hasWall);
  CHECK(hasPath);
}
