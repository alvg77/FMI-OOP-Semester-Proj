/**
 * @file Hero.hpp
 * @ingroup Game
 * @brief Represents a player-controlled hero in the game.
 */

#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include <nlohmann/adl_serializer.hpp>

#include "../Game/Combat/AttackType.hpp"
#include "../Stats/Stats.hpp"
#include "Class/HeroClass.hpp"
#include "Race/HeroRace.hpp"

class Monster;
class Item;
struct Stats;

/**
 * @brief Represents a player-controlled hero in the game.
 *
 * The Hero class encapsulates attributes such as stats, equipment, race, class,
 * and methods for combat, healing, and serialization.
 */
class Hero {
 public:
  /**
   * @brief Constructs a new Hero.
   *
   * @param name The name of the hero.
   * @param level The starting level of the hero.
   * @param stats The initial stat configuration.
   * @param currentHealth The hero's current health value.
   * @param heroRace The hero's race (e.g., Elf, Human).
   * @param heroClass The hero's class (e.g., Warrior, Mage).
   * @param weapon Pointer to the equipped weapon item.
   * @param spell Pointer to the equipped spell item.
   * @param armor Pointer to the equipped armor item.
   */
  Hero(const std::string& name, unsigned level, const Stats& stats,
       double currentHealth, HeroRace heroRace, HeroClass heroClass,
       Item* weapon, Item* spell, Item* armor);

  /**
   * @brief Copy constructor for Hero.
   *
   * @param other The hero to copy from.
   */
  Hero(const Hero& other);

  /**
   * @brief Copy assignment operator.
   *
   * @param other The hero to assign from.
   * @return Reference to this Hero.
   */
  Hero& operator=(const Hero& other);

  /**
   * @brief Destructor.
   *
   * Deallocates all equipped items.
   */
  ~Hero();

  /**
   * @brief Levels up the hero if valid stat points are provided.
   *
   * @param incrementStats The stats to increment on level up.
   * @return True if leveling was successful, false otherwise.
   */
  bool levelUp(const Stats& incrementStats);

  /**
   * @brief Deals damage to a monster using the specified attack type.
   *
   * @param monster The target monster.
   * @param attackType The type of attack to perform.
   */
  void dealDamage(Monster& monster, AttackType attackType) const;

  /**
   * @brief Applies incoming damage to the hero.
   *
   * @param damage The amount of damage taken.
   */
  void takeDamage(double damage);

  /**
   * @brief Heals the hero up to 50% of max health if below it.
   */
  void heal();

  /**
   * @brief Equips a new item, replacing the currently equipped one of the same
   * type.
   *
   * @param item The item to equip.
   */
  void equipItem(Item* item);

  /**
   * @brief Checks whether the hero is still alive.
   *
   * @return True if current health is above zero, false otherwise.
   */
  bool isAlive() const;

  /**
   * @brief Displays hero stats to an output stream.
   *
   * @param os The output stream (default is std::cout).
   */
  void displayStats(std::ostream& os = std::cout) const;

  /**
   * @brief Displays attack damage details.
   *
   * @param os The output stream (default is std::cout).
   */
  void displayAttackDmg(std::ostream& os = std::cout) const;

  /**
   * @brief Displays current status including health and resistance.
   *
   * @param os The output stream (default is std::cout).
   */
  void displayStatus(std::ostream& os = std::cout) const;

  /**
   * @brief Displays currently equipped items and their effects.
   *
   * @param os The output stream (default is std::cout).
   */
  void displayLoadout(std::ostream& os = std::cout) const;

  /**
   * @brief Serializes the hero to a JSON object.
   *
   * Converts the hero's attributes such as name, level, stats, health,
   * race, class, and equipped items into a JSON representation.
   *
   * @return A JSON object representing the hero.
   * @throws nlohmann::json::exception if serialization fails.
   */
  nlohmann::json toJson() const;

 private:
  std::string name;      ///< Hero's name
  unsigned level;        ///< Current level
  Stats stats;           ///< Hero's stats (e.g., strength, mana)
  double currentHealth;  ///< Current health
  HeroRace heroRace;     ///< Hero's race
  HeroClass heroClass;   ///< Hero's class

  Item* armor;   ///< Equipped armor
  Item* weapon;  ///< Equipped weapon
  Item* spell;   ///< Equipped spell

  /**
   * @brief Swaps contents with another hero (used in copy-assignment).
   *
   * @param other The other hero to swap with.
   */
  void swap(Hero& other) noexcept;

  static constexpr unsigned lvlUpPoints =
      30;  ///< Required total points for leveling up
};

#endif  // HERO_HPP
