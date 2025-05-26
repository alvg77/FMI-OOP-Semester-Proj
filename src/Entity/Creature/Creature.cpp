#include "Creature.hpp"

Creature::Creature(const std::string& name, const unsigned level,
                   const Stats& stats, const unsigned levelUpPoints)
    : name(name),
      level(level),
      stats(stats),
      currentHealth(stats.maxHealth),
      levelUpPoints(levelUpPoints) {}

bool Creature::levelUp(const unsigned hp, const unsigned str,
                       const unsigned mn) {
  if (hp + str + mn != levelUpPoints) {
    return false;
  }

  ++level;
  stats.maxHealth += hp;
  currentHealth = stats.maxHealth;
  stats.strength += str;
  stats.mana += mn;

  return true;
}

bool Creature::isAlive() const { return currentHealth > 0; }

std::string Creature::getName() const { return name; }

double Creature::getCurrentHealth() const { return currentHealth; }

unsigned Creature::getStrength() const { return stats.strength; }

unsigned Creature::getMana() const { return stats.mana; }

unsigned Creature::getMaxHealth() const { return stats.maxHealth; }

void Creature::reduceCurrentHealth(const double amount) { currentHealth -= amount; }

void Creature::increaseCurrentHealth(const double amount) { currentHealth += amount; }

void Creature::swap(Creature& other) noexcept {
  using std::swap;

  swap(name, other.name);
  swap(level, other.level);
  swap(stats, other.stats);
  swap(currentHealth, other.currentHealth);
  swap(levelUpPoints, other.levelUpPoints);
}
