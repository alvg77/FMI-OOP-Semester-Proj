/**
 * @file LevelLoader.hpp
 * @ingroup Game
 * @brief Declares the LevelLoader class for constructing game levels from JSON
 * data.
 */

#ifndef LEVELLOADER_HPP
#define LEVELLOADER_HPP

#include <nlohmann/json.hpp>
#include <random>
#include <vector>

class NPEntity;
class Cell;
class Item;
class Monster;
struct Stats;
class Map;

/**
 * @class LevelLoader
 * @brief Loads game levels from JSON files, including the map grid, monsters,
 * and items.
 *
 * Provides static methods to read and validate level data, parse the grid,
 * load monsters and items, and place entities randomly on the map.
 */
class LevelLoader {
 public:
  /**
   * @brief Loads the level with the specified number from JSON files.
   * @param n Level number to load.
   * @return Pointer to a new Map object representing the loaded level.
   * @throws std::runtime_error if files cannot be read or level is invalid.
   */
  static Map* load(unsigned n);

 private:
  /**
   * @brief Validates that the JSON data for the level contains required fields
   * and is consistent.
   * @param data JSON data for the level.
   * @throws std::invalid_argument if validation fails.
   */
  static void validateLevelJson(const nlohmann::json& data);

  /**
   * @brief Reads and parses a JSON file from the given path.
   * @param path File path to the JSON file.
   * @return Parsed JSON object.
   * @throws std::runtime_error if the file cannot be opened.
   */
  static nlohmann::json readJson(const std::string& path);

  /**
   * @brief Parses the JSON grid into a 2D vector of Cell pointers and
   * identifies free spaces.
   * @param jsonGrid JSON array representing the grid.
   * @param grid Reference to the vector to fill with Cell pointers.
   * @param freeSpaces Reference to vector to fill with coordinates of free
   * cells.
   * @param cols Number of columns in the grid.
   * @throws std::invalid_argument if grid data is malformed or contains unknown
   * cell types.
   */
  static void parseGrid(const nlohmann::json& jsonGrid,
                        std::vector<std::vector<Cell*>>& grid,
                        std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
                        unsigned cols);

  /**
   * @brief Loads items for the level from the corresponding JSON file.
   * @param count Number of items to load.
   * @param n Level number (used to select the correct file).
   * @return Vector of pointers to newly created Item entities.
   * @throws std::runtime_error if the file is invalid or does not contain
   * enough items.
   */
  static std::vector<NPEntity*> loadItems(unsigned count, unsigned n);

  /**
   * @brief Loads monsters for the level from the corresponding JSON file.
   * @param count Number of monsters to load.
   * @param n Level number (used to select the correct file).
   * @return Vector of pointers to newly created Monster entities.
   * @throws std::invalid_argument if the file is invalid or does not contain
   * enough monsters.
   */
  static std::vector<NPEntity*> loadMonsters(unsigned count, unsigned n);

  /**
   * @brief Randomly places entities onto free cells in the grid and clears the
   * entities vector.
   * @param entities Vector of entity pointers to place.
   * @param freeCells Vector of free cell coordinates where entities can be
   * placed.
   * @param grid Reference to the game grid.
   */
  static void placeEntitiesAtRandomAndClear(
      std::vector<NPEntity*>& entities,
      std::vector<std::pair<unsigned, unsigned>>& freeCells,
      const std::vector<std::vector<Cell*>>& grid);

  static std::mt19937 rng;  ///< Random number generator instance
  static const std::string levelFileLocation;  ///< Base path for level files
  static const std::string
      monstersFileLocation;                    ///< Base path for monster files
  static const std::string itemsFileLocation;  ///< Base path for item files
};

#endif  // LEVELLOADER_HPP
