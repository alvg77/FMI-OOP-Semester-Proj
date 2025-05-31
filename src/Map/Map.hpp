/**
 * @file Map.hpp
 * @ingroup Game
 * @brief Defines the Map class, which manages the game grid, hero movement, and
 * rendering.
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <random>
#include <vector>

enum class GameAction;
struct LoadedLevel;
class Cell;
class Item;
class NPEntity;
class Hero;

/**
 * @class Map
 * @brief Represents the game map including grid cells, player and finish
 * positions.
 *
 * Manages hero movement, interactions, and rendering of the map.
 */
class Map {
 public:
  /**
   * @brief Constructs a Map object with the given dimensions and layout.
   * @param rows Number of rows in the map grid.
   * @param cols Number of columns in the map grid.
   * @param finishRow Row coordinate of the finish cell.
   * @param finishCol Column coordinate of the finish cell.
   * @param playerRow Initial row position of the player.
   * @param playerCol Initial column position of the player.
   * @param grid 2D vector of pointers to Cell objects representing the map
   * layout.
   */
  Map(unsigned rows, unsigned cols, unsigned finishRow, unsigned finishCol,
      unsigned playerRow, unsigned playerCol,
      const std::vector<std::vector<Cell*>>& grid);

  Map(const Map& other) =
      delete; /**< Deleted copy constructor to avoid copying pointers */
  Map& operator=(const Map& other) =
      delete; /**< Deleted copy assignment operator */

  /**
   * @brief Destructor. Responsible for cleaning up allocated Cell objects.
   */
  ~Map();

  /**
   * @brief Attempts to move the hero in the specified direction.
   * @param hero Reference to the Hero object.
   * @param direction Direction of movement (GameAction enum).
   * @return true if the move was successful, false otherwise.
   */
  bool moveHero(Hero& hero, GameAction direction);

  /**
   * @brief Checks if the hero has reached the finish cell.
   * @return true if the hero is at the finish position, false otherwise.
   */
  bool hasReachedEnd() const;

  /**
   * @brief Displays the current map to the provided output stream.
   * @param os Output stream to write to (defaults to std::cout).
   */
  void display(std::ostream& os = std::cout) const;

  /**
   * @brief Serializes the map state to a JSON object.
   * @return nlohmann::json representation of the current map state.
   */
  nlohmann::json toJson() const;

 private:
  unsigned rows;      /**< Number of rows in the map */
  unsigned cols;      /**< Number of columns in the map */
  unsigned finishRow; /**< Row of the finish cell */
  unsigned finishCol; /**< Column of the finish cell */
  unsigned playerRow; /**< Current row of the player */
  unsigned playerCol; /**< Current column of the player */
  std::vector<std::vector<Cell*>>
      grid; /**< 2D grid of pointers to Cell objects */

  std::mt19937 rng = std::mt19937(
      std::random_device{}()); /**< RNG for any random operations */

  /**
   * @brief Checks if the given coordinates are within the map boundaries.
   * @param row Row index to check.
   * @param col Column index to check.
   * @return true if within bounds, false otherwise.
   */
  bool isWithinBounds(unsigned row, unsigned col) const;
};

#endif  // MAP_HPP
