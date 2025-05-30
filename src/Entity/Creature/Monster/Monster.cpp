#include "Monster.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#include "../../../Game/Combat/CombatManager.hpp"
#include "../../../Game/Interactions/InteractionsManager.hpp"
#include "../Hero/Hero.hpp"
#include "../Stats.hpp"

Monster::Monster(const std::string& name, const unsigned level,
                 const Stats& stats, const double scalesDefenceMult)
    : name(name),
      level(level),
      stats(stats),
      scalesDefenceMult(scalesDefenceMult),
      currentHealth(stats.maxHealth) {}

void Monster::dealDamage(Hero& hero) const {
  hero.takeDamage(static_cast<double>(stats.strength + stats.mana) / 2);
}

void Monster::takeDamage(const double damage) {
  currentHealth -= damage - scalesDefenceMult * damage;
}

bool Monster::onStep(Hero& hero) {
  std::cout << "You have encountered a " << name << std::endl;
  InteractionsManager::promptContinue();

  return true;
}

void Monster::onInteract(Hero& hero) {
  CombatManager::initiateCombat(hero, *this);
  if (!isAlive()) {
    NPEntity::status = NPEntityStatus::INACTIVE;
  }
}

char Monster::getSymbol() const { return monsterSymbol; }

Monster* Monster::clone() const { return new Monster(*this); }

bool Monster::isAlive() const { return currentHealth > 0; }

void Monster::displayStatus(std::ostream& os) const {
  os << name << ": " << (currentHealth >= 0 ? currentHealth : 0) << "/"
     << stats.maxHealth << std::endl;
  os << "Resistance: " << scalesDefenceMult << std::endl;
}

nlohmann::json Monster::toJson() const {
  using nlohmann::json;
  json monsterJson;

  monsterJson["name"] = name;
  monsterJson["level"] = level;
  monsterJson["strength"] = stats.maxHealth;
  monsterJson["mana"] = stats.mana;
  monsterJson["maxhealth"] = stats.maxHealth;
  monsterJson["scalesdefencemult"] = scalesDefenceMult;

  return monsterJson;
}
