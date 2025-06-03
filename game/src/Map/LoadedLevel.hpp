/**
 * @file LoadedLevel.hpp
 * @ingroup Game
 * @brief Declares the LoadedLevel struct, which represents a complete game
 * level layout.
 */

#ifndef LOADEDLEVEL_HPP
#define LOADEDLEVEL_HPP

/**
 * @struct LoadedLevel
 * @brief Represents a fully loaded level including grid layout and key
 * positions.
 *
 * Contains the number of rows and columns, the player's starting position,
 * the finish cell coordinates, and the 2D grid of cells.
 */
struct LoadedLevel {
  unsigned rows{};      /**< Number of rows in the level grid */
  unsigned cols{};      /**< Number of columns in the level grid */
  unsigned playerRow{}; /**< Starting row position of the player */
  unsigned playerCol{}; /**< Starting column position of the player */
  unsigned finishRow{}; /**< Row coordinate of the finish cell */
  unsigned finishCol{}; /**< Column coordinate of the finish cell */
  std::vector<std::vector<Cell*>>
      grid; /**< 2D grid representing the level layout */
};

#endif  // LOADEDLEVEL_HPP
