/**
 * @file HeroRace.hpp
 * @ingroup Game
 * @brief Enum representing the available hero races.
 */

#ifndef HERORACE_HPP
#define HERORACE_HPP

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

#endif  // HERORACE_HPP
