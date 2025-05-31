/**
 * @file ItemType.hpp
 * @ingroup Game
 * @brief Defines the ItemType enum and utility functions for item type
 * handling.
 */

#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP

#include <string>

/**
 * @enum ItemType
 * @brief Represents different types of items in the game.
 */
enum class ItemType {
  WEAPON,  ///< Weapon item (e.g., sword, axe)
  SPELL,   ///< Spell item (e.g., fireball, heal)
  ARMOR    ///< Armor item (e.g., helmet, shield)
};

/**
 * @brief Converts an ItemType enum to its string representation.
 * @param itemType The ItemType to convert.
 * @return A string view representing the item type ("weapon", "spell",
 * "armor").
 */
std::string_view getItemTypeName(const ItemType itemType);

/**
 * @brief Converts a string to the corresponding ItemType enum.
 * @param itemTypeStr A string representing the item type.
 * @return The corresponding ItemType.
 * @throws std::invalid_argument if the input string does not match a known
 * type.
 */
ItemType getItemType(const std::string& itemTypeStr);

#endif  // ITEMTYPE_HPP
