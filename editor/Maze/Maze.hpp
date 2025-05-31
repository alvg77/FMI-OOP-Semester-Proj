/**
 * @file Maze.hpp
 * @ingroup LevelEditor
 * @brief Defines the Maze class representing a grid of walls and paths.
 */

#ifndef MAZE_HPP
#define MAZE_HPP

#include <nlohmann/json_fwd.hpp>
#include <vector>

/**
 * @class Maze
 * @brief Represents a maze grid consisting of walls and paths.
 *
 * The maze is stored as a 2D grid where each cell is either a wall or a path.
 * Supports setting paths, checking walls, retrieving neighbors for maze
 * generation, displaying the maze, and exporting to JSON.
 */
class Maze {
 public:
  /**
   * @brief Constructs a Maze of given dimensions filled with walls.
   * @param rows Number of rows in the maze.
   * @param cols Number of columns in the maze.
   */
  Maze(unsigned rows, unsigned cols);

  /**
   * @brief Marks the cell at (row, col) as a path (walkable).
   * @param row Row index of the cell.
   * @param col Column index of the cell.
   */
  void setPath(unsigned row, unsigned col);

  /**
   * @brief Checks if the cell at (row, col) is a wall.
   * @param row Row index of the cell.
   * @param col Column index of the cell.
   * @return True if the cell is a wall, false otherwise.
   */
  bool isWall(unsigned row, unsigned col) const;

  /**
   * @brief Returns a list of neighbor cells two steps away that are walls.
   *
   * Used during maze generation to find candidate cells to carve paths into.
   * The two-step offset ensures walls between cells are properly handled.
   *
   * @param row Row index of the current cell.
   * @param col Column index of the current cell.
   * @return Vector of (row, col) pairs representing neighbor cells.
   */
  std::vector<std::pair<unsigned, unsigned>> getNeighbours(unsigned row,
                                                           unsigned col) const;

  /**
   * @brief Prints the maze grid to standard output.
   *
   * Walls are shown as '#' and paths as '.'.
   */
  void display() const;

  /**
   * @brief Serializes the maze grid and metadata to JSON.
   * @return A JSON object containing rows, columns, and the grid data.
   */
  nlohmann::json toJson() const;

  /**
   * @brief Checks if a given (row, col) coordinate is within the maze bounds.
   * @param row Row index to check.
   * @param col Column index to check.
   * @return True if (row, col) is inside the grid, false otherwise.
   */
  bool isWithinBounds(unsigned row, unsigned col) const;

 private:
  unsigned rows;  ///< Number of rows in the maze
  unsigned cols;  ///< Number of columns in the maze
  std::vector<std::vector<unsigned>>
      grid;  ///< 2D grid representing walls and paths
};

#endif  // MAZE_HPP
