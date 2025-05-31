/**
 * @file Item.hpp
 * @ingroup Game
 * @brief Declaration of the Item class representing collectible game items.
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <nlohmann/json_fwd.hpp>
#include <string>

#include "../NPEntity.hpp"
#include "ItemType.hpp"

/**
 * @brief Represents a collectible item that the hero can pick up and equip.
 *
 * Inherits from NPEntity and defines behavior for picking up and interacting
 * with items. Each item provides a bonus and belongs to a specific item type,
 * such as weapon, spell, or armor.
 */
class Item final : public NPEntity {
 public:
  /**
   * @brief Constructs an item with a name, bonus value, and item type.
   * @param name Name of the item.
   * @param mult Bonus multiplier or stat the item provides.
   * @param itemType Type of the item (weapon, spell, armor).
   */
  Item(const std::string& name, double mult, ItemType itemType);

  /**
   * @brief Gets the name of the item.
   * @return The item's name.
   */
  std::string getName() const;

  /**
   * @brief Gets the item's bonus value.
   * @return The item's bonus multiplier.
   */
  double getMult() const;

  /**
   * @brief Gets the type of the item.
   * @return The item's type as an ItemType enum.
   */
  ItemType getItemType() const;

  /**
   * @brief Handles behavior when the Hero steps on the item.
   * @param hero Reference to the Hero stepping on the item.
   * @return Always returns true to indicate the item can be picked up.
   */
  bool onStep(Hero& hero) override;

  /**
   * @brief Handles interaction behavior (e.g., equipping the item).
   * @param hero Reference to the Hero interacting with the item.
   */
  void onInteract(Hero& hero) override;

  /**
   * @brief Gets the character symbol representing this item on the map.
   * @return The character 'T'.
   */
  char getSymbol() const override;

  /**
   * @brief Creates a clone (deep copy) of this item.
   * @return A pointer to a new Item with the same data.
   */
  Item* clone() const override;

  /**
   * @brief Serializes the item to a JSON object.
   * @return A JSON object representing the item's state.
   */
  nlohmann::json toJson() const override;

  /**
   * @brief Stream insertion operator for item display.
   * @param os Output stream to write to.
   * @param item The item to output.
   * @return Reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const Item& item);

 private:
  std::string name;   ///< Name of the item.
  double mult;     ///< Bonus multiplier provided by the item.
  ItemType itemType;  ///< Type of the item (weapon, spell, armor).

  static constexpr char treasureSymbol = 'T';  ///< Map symbol for items.
};

/**
 * @brief Stream insertion operator for displaying item information.
 */
std::ostream& operator<<(std::ostream& os, const Item& item);

#endif  // ITEM_HPP
