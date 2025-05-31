/**
 * @file HeroRace.hpp
 * @ingroup Game
 * @brief Enum representing the available hero races.
 */

#ifndef HERORACE_HPP
#define HERORACE_HPP

#include <string>

/**
 * @brief Enum representing the available hero races.
 *
 * Used to determine the racial bonuses and characteristics
 * applied to a hero upon creation.
 */
enum class HeroRace {
  HUMAN,  ///< Balanced race with moderate stat bonuses.
  ELF     ///< Magic-oriented race with higher mana and health bonuses.
};

/**
 * @brief Returns the string name of the given HeroRace.
 *
 * @param heroRace The hero race enum value.
 * @return A string view representing the hero race name.
 */
std::string_view getHeroRaceName(HeroRace heroRace);

/**
 * @brief Converts a string to the corresponding HeroRace enum value.
 *
 * @param heroRaceStr The string representing the hero race.
 * @return The corresponding HeroRace enum.
 * @throws std::invalid_argument if the string does not match any HeroRace.
 */
HeroRace getHeroRace(const std::string& heroRaceStr);

#endif  // HERORACE_HPP
