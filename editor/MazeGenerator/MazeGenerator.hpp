/**
 * @file MazeGenerator.hpp
 * @ingroup Level Editor
 * @brief Generates mazes using depth-first search algorithm.
 */

#ifndef MAZEGENERATOR_HPP
#define MAZEGENERATOR_HPP

class Maze;

/**
 * @brief Generates a maze using depth-first search.
 */
class MazeGenerator {
 public:
  /**
   * @brief Generate a maze with given dimensions.
   *
   * The maze is represented as a grid with paths carved between cells.
   * The algorithm uses DFS with a stack to create a perfect maze.
   *
   * @param rows Number of rows in the maze grid.
   * @param cols Number of columns in the maze grid.
   * @return Maze The generated maze.
   */
  static Maze generate(unsigned rows, unsigned cols);
};

#endif  // MAZEGENERATOR_HPP
