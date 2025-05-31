/**
 * @file GameAction.hpp
 * @ingroup Game
 * @brief Defines enumerated values representing user input actions during
 * gameplay.
 */

#ifndef GAMEACTION_HPP
#define GAMEACTION_HPP

/**
 * @enum GameAction
 * @brief Represents possible player input actions in the game.
 */
enum class GameAction {
  MOVE_UP,     ///< Move the player up
  MOVE_DOWN,   ///< Move the player down
  MOVE_LEFT,   ///< Move the player left
  MOVE_RIGHT,  ///< Move the player right
  SAVE,        ///< Save the current game state
  EXIT         ///< Exit the game
};

#endif  // GAMEACTION_HPP
