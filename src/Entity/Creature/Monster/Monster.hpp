/**
 * @file Monster.hpp
 * @ingroup Game
 * @brief Defines the Monster class representing hostile entities in the game.
 */

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <iostream>
#include <nlohmann/json_fwd.hpp>

#include "../../NPEntity.hpp"
#include "../Stats.hpp"

/**
 * @brief Represents a monster entity that the hero can encounter and fight.
 *
 * Inherits from NPEntity and defines combat behavior, stats, and interaction
 * with the hero.
 */
class Monster final : public NPEntity {
 public:
  /**
   * @brief Constructs a Monster with given attributes.
   *
   * @param name The monster's name.
   * @param level The monster's level.
   * @param stats The monster's combat stats.
   * @param scalesDefenceMult Multiplier applied to incoming damage for
   * resistance scaling.
   */
  Monster(const std::string& name, unsigned level, const Stats& stats,
          double scalesDefenceMult);

  /**
   * @brief Attacks the hero and deals damage.
   *
   * @param hero The hero receiving the damage.
   */
  void dealDamage(Hero& hero) const;

  /**
   * @brief Reduces the monster's health based on incoming damage.
   *
   * @param damage The amount of damage to apply.
   */
  void takeDamage(double damage);

  /**
   * @brief Called when a hero steps on the monster's cell.
   *
   * @param hero The hero stepping onto the monster.
   * @return true Always returns true (combat initiated).
   */
  bool onStep(Hero& hero) override;

  /**
   * @brief Called when the hero interacts with the monster.
   *
   * @param hero The interacting hero.
   */
  void onInteract(Hero& hero) override;

  /**
   * @brief Returns the symbol used to represent the monster on the map.
   *
   * @return Character symbol 'M'.
   */
  char getSymbol() const override;

  /**
   * @brief Clones the monster object.
   *
   * @return Pointer to a new copy of the monster.
   */
  Monster* clone() const override;

  /**
   * @brief Checks if the monster is still alive.
   *
   * @return True if current health is greater than 0.
   */
  bool isAlive() const;

  /**
   * @brief Displays the monster's current status to the given output stream.
   *
   * @param os Output stream to display status (default is std::cout).
   */
  void displayStatus(std::ostream& os = std::cout) const;

  /**
   * @brief Serializes the monster to a JSON object.
   *
   * @return JSON representation of the monster.
   */
  nlohmann::json toJson() const override;

 private:
  std::string name;          ///< The monster's name.
  unsigned level;            ///< The monster's level.
  Stats stats;               ///< The monster's stats (strength, mana, health).
  double scalesDefenceMult;  ///< Resistance multiplier for incoming damage.
  double currentHealth;      ///< Current health points.
  static constexpr char monsterSymbol = 'M';  ///< Map symbol for monster.
};

#endif  // MONSTER_HPP
