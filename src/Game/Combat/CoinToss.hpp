#ifndef COINTOSS_HPP
#define COINTOSS_HPP

#include <ostream>

enum class CoinToss { HEADS, TAILS };

inline std::ostream& operator<<(std::ostream& os, const CoinToss& other) {
  switch (other) {
    case CoinToss::HEADS:
      os << "Heads";
      break;
    case CoinToss::TAILS:
      os << "Tails";
      break;
  }
  return os;
}

#endif  // COINTOSS_HPP
