/**
 * @file ItemFactory.hpp
 * @ingroup Game
 * @brief Factory for creating Items from JSON data.
 */

#ifndef ITEMFACTORY_HPP
#define ITEMFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class NPEntity;
class Item;

/**
 * @brief Factory class responsible for creating Item instances from JSON data.
 *
 * Provides a static method to deserialize item data and return it as a
 * polymorphic NPEntity pointer.
 */
class ItemFactory {
 public:
  /**
   * @brief Creates an Item from a JSON object.
   *
   * Parses the item name, multiplier (bonus), and type from the JSON structure and returns a
   * pointer to a new Item instance wrapped as an NPEntity.
   *
   * @param itemJson A JSON object containing fields: "name", "mult", and "itemtype".
   * @return A dynamically allocated Item as a NPEntity pointer.
   * @throws std::runtime_error if the multiplier value is negative.
   * @throws nlohmann::json::exception if required fields are missing or have incorrect types.
   */
  static NPEntity* createItemFromJson(const nlohmann::json& itemJson);
};

#endif  // ITEMFACTORY_HPP
