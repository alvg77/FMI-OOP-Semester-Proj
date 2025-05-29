#include "Monster.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#include "../../../Game/Combat/CombatManager.hpp"
#include "../../../Game/Interactions/InteractionsManager.hpp"
#include "../Hero/Hero.hpp"

Monster::Monster(const std::string& name, const unsigned level,
                 const Stats initialStats)
    : Creature(name, level, initialStats), scalesDefenceMult(0.15) {
  for (unsigned i = 1; i < level; ++i) {
    scalesDefenceMult += 0.05;
    Creature::increaseStats({10, 10, 20});
  }
}

Monster::Monster(const nlohmann::json& monsterJson)
    : Creature(monsterJson), scalesDefenceMult(0) {
  loadJson(monsterJson);
}

void Monster::dealDamage(Hero& hero) const {
  hero.takeDamage(static_cast<double>(getStrength() + getMana()) / 2);
}

void Monster::takeDamage(const double damage) {
  reduceCurrentHealth(damage - scalesDefenceMult * damage);
}

bool Monster::onStep(Hero& hero) {
  std::cout << "You have encountered a " << getName() << std::endl;
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

nlohmann::json Monster::toJson() const {
  using nlohmann::json;

  json monsterJson = Creature::toJson();
  monsterJson["scales_defence_mult"] = scalesDefenceMult;

  return monsterJson;
}

void Monster::loadJson(const nlohmann::json& monsterJson) {
  scalesDefenceMult = monsterJson["scales_defence_mult"];
}
