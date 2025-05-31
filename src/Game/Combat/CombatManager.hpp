/**
 * @file CombatManager.hpp
 * @ingroup Game
 * @brief Manages combat logic and flow between Hero and Monster entities.
 *
 * Provides static methods to initiate combat, determine turn order via coin
 * toss, and handle attack phases during combat encounters.
 */

#ifndef COMBATMANAGER_HPP
#define COMBATMANAGER_HPP

#include "../../NPEntity/Monster/Monster.hpp"
#include "CoinToss.hpp"

class Monster;
class Hero;

/**
 * @brief Facilitates turn-based battles between the hero and monsters.
 *
 * The CombatManager oversees the entire encounter process, including
 * determining who goes first, executing attack turns, and concluding combat
 * based on victory conditions.
 */
class CombatManager {
 public:
  /**
   * @brief Starts a combat encounter between the hero and a monster.
   *
   * Runs a turn-based combat loop until either the hero or monster is defeated.
   *
   * @param hero Reference to the hero participating in combat.
   * @param monster Reference to the monster participating in combat.
   */
  static void initiateCombat(Hero& hero, Monster& monster);

 private:
  /**
   * @brief Simulates a coin toss to decide who attacks first.
   *
   * @return CoinToss enum value HEADS or TAILS.
   */
  static CoinToss coinToss();

  /**
   * @brief Executes the player's attack turn.
   *
   * Allows the hero to choose between weapon or spell attack.
   *
   * @param hero The attacking hero.
   * @param monster The defending monster.
   */
  static void playerAttack(const Hero& hero, Monster& monster);

  /**
   * @brief Executes the monster's attack turn.
   *
   * @param hero The defending hero.
   * @param monster The attacking monster.
   */
  static void monsterAttack(Hero& hero, const Monster& monster);
};

#endif  // COMBATMANAGER_HPP
