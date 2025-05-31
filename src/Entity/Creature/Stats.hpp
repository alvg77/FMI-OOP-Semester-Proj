/**
 * @file Stats.hpp
 * @ingroup Game
 * @brief Defines the Stats struct representing character or monster attributes.
 */

#ifndef STATS_HPP
#define STATS_HPP

/**
 * @brief Represents the primary attributes of a character or monster.
 *
 * Includes strength (physical power), mana (magical power), and maxHealth
 * (maximum HP).
 */
struct Stats {
  /**
   * @brief The physical strength stat.
   */
  unsigned strength;

  /**
   * @brief The magical power stat.
   */
  unsigned mana;

  /**
   * @brief The maximum health stat.
   */
  unsigned maxHealth;

  /**
   * @brief Adds two Stats objects component-wise.
   *
   * This operator returns a new Stats object whose fields are the sum
   * of the corresponding fields of the current and the other Stats object.
   *
   * @param other The Stats object to add.
   * @return A new Stats object containing the component-wise sum.
   */
  Stats operator+(const Stats& other) const;
};

#endif  // STATS_HPP
