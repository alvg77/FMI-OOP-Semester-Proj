/**
 * @file HeroClass.hpp
 * @ingroup Game
 * @brief Enum representing the available hero classes.
 */

#ifndef HEROCLASS_HPP
#define HEROCLASS_HPP

/**
 * @brief Enum representing the available hero classes.
 *
 * Hero classes define the combat style and initial stats
 * of a hero character.
 */
enum class HeroClass {
  WARRIOR,  ///< Focused on physical strength and melee combat.
  MAGE      ///< Specializes in magic attacks and higher mana.
};

#endif  // HEROCLASS_HPP
