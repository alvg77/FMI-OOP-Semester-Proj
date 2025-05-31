/**
 * @file InteractionsManager.hpp
 * @ingroup Game
 * @brief Handles player interaction prompts such as equipping items and
 * leveling up.
 */

#ifndef INTERACTIONSMANAGER_HPP
#define INTERACTIONSMANAGER_HPP

class Hero;
struct Item;

/**
 * @brief Provides static methods to prompt the player for key interactions.
 *
 * Includes prompts for equipping items, leveling up, and pausing gameplay.
 */
class InteractionsManager {
 public:
  /**
   * @brief Prompts the hero to decide whether to equip a newly found item.
   *
   * Displays the item details and the hero’s current loadout.
   *
   * @param hero Reference to the hero.
   * @param item Pointer to the item found.
   */
  static void promptHeroItemEquip(Hero& hero, const Item* item);

  /**
   * @brief Prompts the hero to allocate attribute points when leveling up.
   *
   * Displays current stats and enforces valid allocation.
   *
   * @param hero Reference to the hero.
   */
  static void promptHeroLevelUp(Hero& hero);

  /**
   * @brief Prompts the user to press enter to continue.
   */
  static void promptContinue();
};

#endif
