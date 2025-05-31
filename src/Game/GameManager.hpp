/**
 * @file GameManager.hpp
 * @ingroup Game
 * @brief Declares the GameManager class, which controls the main game loop and
 * state transitions.
 */

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../Map/Map.hpp"
#include "GameContext.hpp"

class Monster;
class Item;

/**
 * @class GameManager
 * @brief Controls the main game loop, game state, and level progression.
 *
 * Manages hero creation/loading, map management, user input handling,
 * saving/loading game state, and overall game flow.
 */
class GameManager {
 public:
  /**
   * @brief Constructs a new GameManager instance.
   */
  GameManager();

  /**
   * @brief Deleted copy constructor.
   */
  GameManager(const GameManager& other) = delete;

  /**
   * @brief Deleted copy assignment operator.
   */
  GameManager& operator=(const GameManager& other) = delete;

  /**
   * @brief Destructs the GameManager, cleaning up allocated resources.
   */
  ~GameManager();

  /**
   * @brief Starts and runs the main game loop until exit or game completion.
   */
  void runGameLoop();

 private:
  static constexpr unsigned nlevels = 4;      ///< Total number of game levels
  static const std::string saveFileLocation;  ///< Location of the save file

  unsigned level;   ///< Current game level
  GameContext ctx;  ///< Current game context holding hero and map
};

#endif  // GAMEMANAGER_HPP
