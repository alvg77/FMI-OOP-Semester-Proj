/**
 * @file GameEditor.hpp
 * @ingroup Editor
 * @brief Provides tools to create and edit game levels.
 */

#ifndef GAMEEDITOR_HPP
#define GAMEEDITOR_HPP
#include <string>

class Maze;

/**
 * @class GameEditor
 * @brief Provides functionality to create and edit game levels.
 *
 * Allows generating maze levels, specifying monsters, treasures, finish
 * position, and saving the level configuration to a JSON file.
 */
class GameEditor {
 public:
  /**
   * @brief Starts the interactive game level editor.
   *
   * Prompts the user for level parameters, generates a maze, and saves the
   * level.
   */
  static void editGameDetails();

 private:
  /**
   * @brief Saves the generated level data to a JSON file.
   *
   * @param n Level number.
   * @param maze Maze object containing the level layout.
   * @param treasureN Number of treasures in the level.
   * @param monsterN Number of monsters in the level.
   * @param finishRow Row index of the finish cell.
   * @param finishCol Column index of the finish cell.
   * @throws std::runtime_error if the level file cannot be opened or created.
   */
  static void saveLevel(unsigned n, const Maze& maze, unsigned treasureN,
                        unsigned monsterN, unsigned finishRow,
                        unsigned finishCol);

  static constexpr unsigned levelsN = 4; /**< Number of levels supported. */
  static const std::string
      levelMapLocation; /**< Directory where levels are saved. */
};

#endif  // GAMEEDITOR_HPP
