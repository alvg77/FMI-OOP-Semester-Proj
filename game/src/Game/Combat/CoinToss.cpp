#include "CoinToss.hpp"

std::ostream& operator<<(std::ostream& os, const CoinToss& other) {
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
