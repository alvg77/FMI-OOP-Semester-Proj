#include "Monster.hpp"

#include <iostream>

#include "../../../Game/Combat/CombatManager.hpp"
#include "../Hero/Hero.hpp"

Monster::Monster(const std::string& name, const unsigned level,
                 const Stats stats)
    : Creature(name, level, stats, 30), scalesDefenceMult(0.15) {
  for (unsigned i = 1; i < level; ++i) {
    levelUp();
  }
}

void Monster::dealDamage(Hero& hero) const {
  hero.takeDamage(static_cast<double>(getStrength() + getMana()) / 2);
}

void Monster::takeDamage(const double damage) {
  reduceCurrentHealth(damage - scalesDefenceMult * damage);
}

void Monster::levelUp() {
  scalesDefenceMult += 0.05;
  Creature::levelUp(10, 10, 10);
}

bool Monster::onStep(Hero& hero) {
  std::cout << "You have encountered a " << getName() << std::endl;
  return true;
}

void Monster::onInteract(Hero& hero) {
  CombatManager::initiateCombat(hero, *this);
  if (!isAlive()) {
    NPEntity::status = NPEntityStatus::INACTIVE;
  }
}

char Monster::getSymbol() const {
  return monsterSymbol;
}

NPEntity* Monster::clone() const {
  return new Monster(*this);
}
