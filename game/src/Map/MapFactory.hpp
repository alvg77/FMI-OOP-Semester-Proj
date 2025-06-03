/**
 * @file MapFactory.hpp
 * @ingroup Game
 * @brief Creates Map instances from level files or JSON data.
 */

#ifndef MAPFACTORY_HPP
#define MAPFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class Map;

/**
 * @class MapFactory
 * @brief Factory class to create Map instances.
 *
 * Provides methods to create maps either by loading level data from files
 * or by deserializing from JSON data.
 */
class MapFactory {
 public:
  /**
   * @brief Creates a Map by loading level data from the predefined level files.
   * @param level The level number to load.
   * @return Pointer to the newly created Map object.
   *
   * This method internally uses LevelLoader to load the map.
   */
  static Map* createMap(unsigned level);

  /**
   * @brief Creates a Map instance from JSON data.
   * @param mapJson JSON object representing the serialized map data.
   * @return Pointer to the newly created Map object.
   * @throws std::runtime_error if invalid values for monster and treasure
   * coordinates are out of bounds when reading them from JSON.
   *
   * This method reconstructs the map grid, including walls, monsters, and
   * items, from the JSON representation.
   */
  static Map* createMapFromJson(const nlohmann::json& mapJson);
};

#endif  // MAPFACTORY_HPP
