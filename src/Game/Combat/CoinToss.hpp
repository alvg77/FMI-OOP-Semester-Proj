/**
 * @file CoinToss.hpp
 * @ingroup Game
 * @brief Defines the CoinToss enum representing the outcomes of a coin toss,
 *        and provides stream output functionality.
 */

#ifndef COINTOSS_HPP
#define COINTOSS_HPP

#include <ostream>

/**
 * @enum CoinToss
 * @brief Represents the possible outcomes of a coin toss.
 */
enum class CoinToss {
  HEADS,  ///< The coin lands on heads.
  TAILS   ///< The coin lands on tails.
};

/**
 * @brief Inserts a textual representation of a CoinToss into an output stream.
 *
 * Converts HEADS to "Heads" and TAILS to "Tails".
 *
 * @param os    The output stream to write to.
 * @param other The CoinToss value to insert.
 * @return      A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const CoinToss& other);

#endif  // COINTOSS_HPP
