/**
 * @file SaveManager.hpp
 * @ingroup Game
 * @brief Handles serialization and deserialization of the game state to/from
 * disk.
 */

#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include <nlohmann/json_fwd.hpp>
#include <string>

struct GameContext;
class Map;
class Hero;

/**
 * @brief Provides static methods for saving and loading the game state.
 *
 * Saves the current game context (hero and map) to a JSON file and loads it
 * back.
 */
class SaveManager {
 public:
  /**
   * @brief Saves the current game context to a file.
   *
   * @param ctx The game context containing the hero and map to save.
   * @throws std::runtime_error If hero or map pointers are null.
   * @throws std::invalid_argument If the save file cannot be opened.
   */
  static void save(const GameContext& ctx);

  /**
   * @brief Loads the game context from the save file.
   *
   * @return The loaded game context.
   * @throws std::runtime_error If the save file does not exist or cannot be
   * opened.
   */
  static GameContext loadGame();

 private:
  /// File location for the saved game JSON data.
  static const std::string saveFileLoc;
};

#endif  // SAVEMANAGER_HPP
