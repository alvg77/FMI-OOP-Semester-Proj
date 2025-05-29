#include "Creature.hpp"

#include <nlohmann/json.hpp>

Creature::Creature(const std::string& name, const unsigned level,
                   const Stats& stats)
    : name(name), level(level), stats(stats), currentHealth(stats.maxHealth) {}

Creature::Creature(const nlohmann::json& creatureJson)
    : level(1), stats({}), currentHealth(0) {
  Creature::loadJson(creatureJson);
}

bool Creature::isAlive() const { return currentHealth > 0; }

std::string Creature::getName() const { return name; }

double Creature::getCurrentHealth() const {
  return currentHealth > 0 ? currentHealth : 0;
}

unsigned Creature::getStrength() const { return stats.strength; }

unsigned Creature::getMana() const { return stats.mana; }

unsigned Creature::getMaxHealth() const { return stats.maxHealth; }

nlohmann::json Creature::toJson() const {
  using nlohmann::json;

  json creatureJson;

  creatureJson["name"] = name;
  creatureJson["level"] = level;
  creatureJson["strength"] = stats.strength;
  creatureJson["mana"] = stats.mana;
  creatureJson["maxhealth"] = stats.maxHealth;
  creatureJson["currenthealth"] = currentHealth;

  return creatureJson;
}

void Creature::reduceCurrentHealth(const double amount) {
  currentHealth -= amount;
}

void Creature::increaseCurrentHealth(const double amount) {
  currentHealth += amount;
}

void Creature::increaseStats(const Stats& stats) {
  this->stats = this->stats + stats;
}

void Creature::swap(Creature& other) noexcept {
  using std::swap;

  swap(name, other.name);
  swap(level, other.level);
  swap(stats, other.stats);
  swap(currentHealth, other.currentHealth);
}

void Creature::loadJson(const nlohmann::json& creatureJson) {
  name = creatureJson["name"];
  level = creatureJson["level"];
  stats.strength = creatureJson["strength"];
  stats.mana = creatureJson["mana"];
  stats.maxHealth = creatureJson["maxhealth"];
  currentHealth = creatureJson["currenthealth"];
}
