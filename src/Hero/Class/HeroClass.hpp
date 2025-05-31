/**
 * @file HeroClass.hpp
 * @ingroup Game
 * @brief Enum representing the available hero classes.
 */

#ifndef HEROCLASS_HPP
#define HEROCLASS_HPP

#include <string>

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

/**
 * @brief Returns the string name of the given HeroClass.
 *
 * @param heroClass The hero class enum value.
 * @return A string view representing the hero class name.
 */
std::string_view getHeroClassName(HeroClass heroClass);

/**
 * @brief Converts a string to the corresponding HeroClass enum value.
 *
 * @param heroClassStr The string representing the hero class.
 * @return The corresponding HeroClass enum.
 * @throws std::invalid_argument if the string does not match any HeroClass.
 */
HeroClass getHeroClass(const std::string& heroClassStr);

#endif  // HEROCLASS_HPP
