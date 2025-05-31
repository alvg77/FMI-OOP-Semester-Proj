/**
 * @file CellState.hpp
 * @ingroup LevelEditor
 * @brief Defines the CellState enum representing maze cell states.
 */

#ifndef CELLSTATE_HPP
#define CELLSTATE_HPP

/**
 * @enum CellState
 * @brief Represents the state of a cell in the maze grid.
 *
 * A cell can either be a WALL (non-walkable) or a PATH (walkable).
 */
enum CellState {
  WALL = 1, /**< Indicates the cell is a wall (blocked). */
  PATH = 0  /**< Indicates the cell is a path (walkable). */
};

#endif  // CELLSTATE_HPP
