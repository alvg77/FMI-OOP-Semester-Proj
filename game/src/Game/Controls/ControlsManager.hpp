/**
 * @file ControlsManager.hpp
 * @ingroup Game
 * @brief Handles user input and translates it into actionable game commands.
 */

#ifndef CONTROLSMANAGER_HPP
#define CONTROLSMANAGER_HPP

#include "../../Map/Map.hpp"

/**
 * @brief Manages input controls and maps key presses to game actions.
 */
class ControlsManager {
 public:
  /**
   * @brief Waits for and returns the next user input as a GameAction.
   *
   * Reads input from the terminal or console and translates arrow keys, save,
   * and exit commands into appropriate game actions.
   *
   * @return The corresponding GameAction enum value for the input.
   */
  static GameAction getInputs();
};

#endif  // CONTROLSMANAGER_HPP
