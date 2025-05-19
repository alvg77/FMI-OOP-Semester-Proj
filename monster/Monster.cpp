#include "Monster.hpp"

#include "../character/Character.hpp"

Monster::Monster() : level(1), strength(25), mana(25), health(25) {}

Monster::Monster(const unsigned level, const unsigned strength,
                        const unsigned mana, const unsigned health)
    : level(level), strength(strength), mana(mana), health(health) {}

void Monster::takeDamage(const unsigned damage) {
  health -= damage - (damage * Monster::dmgReduction / 100);
}

// figure out how monsters deal actual damage
void Monster::dealDamage(Character& character) const {
  character.takeDamage(strength);
}
