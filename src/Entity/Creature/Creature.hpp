#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <nlohmann/adl_serializer.hpp>
#include <string>

#include "Stats.hpp"

class Creature {
 public:
  Creature(const std::string& name, unsigned level, const Stats& stats);
  explicit Creature(const nlohmann::json& creatureJson);
  virtual ~Creature() = default;

  virtual void takeDamage(double damage) = 0;

  bool isAlive() const;

  virtual nlohmann::json toJson() const;

  std::string getName() const;
  double getCurrentHealth() const;
  unsigned getStrength() const;
  unsigned getMana() const;
  unsigned getMaxHealth() const;

 protected:
  void reduceCurrentHealth(double amount);
  void increaseCurrentHealth(double amount);

  void increaseStats(const Stats& stats);

  void swap(Creature& other) noexcept;

 private:
  std::string name;
  unsigned level;
  Stats stats;
  double currentHealth;

  virtual void loadJson(const nlohmann::json& creatureJson);
};

#endif  // CREATURE_HPP
