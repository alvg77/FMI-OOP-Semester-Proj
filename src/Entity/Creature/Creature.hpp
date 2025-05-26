#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>

#include "Stats.hpp"

class Creature {
 public:
  Creature(const std::string& name, unsigned level, const Stats& stats,
           unsigned levelUpPoints);
  virtual ~Creature() = default;

  virtual void takeDamage(double damage) = 0;

  bool levelUp(unsigned hp, unsigned str, unsigned mn);

  bool isAlive() const;

  std::string getName() const;
  double getCurrentHealth() const;
  unsigned getStrength() const;
  unsigned getMana() const;
  unsigned getMaxHealth() const;

protected:
  void reduceCurrentHealth(double amount);
  void increaseCurrentHealth(double amount);

  void swap(Creature& other) noexcept;

 private:
  std::string name;
  unsigned level;
  Stats stats;
  double currentHealth;
  unsigned levelUpPoints;
};

#endif  // CREATURE_HPP
