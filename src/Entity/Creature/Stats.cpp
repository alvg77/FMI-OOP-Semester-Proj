#include "Stats.hpp"

Stats Stats::operator+(const Stats& other) const {
  return {strength + other.strength, mana + other.mana,
          maxHealth + other.maxHealth};
}