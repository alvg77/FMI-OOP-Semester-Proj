//
// Created by Alek on 5/17/2025.
//

#include "Monster.hpp"

inline Monster::Monster()
    : level(1),
      strength(25),
      mana(25),
      health(25)
{}

inline Monster::Monster(unsigned level, unsigned strength, unsigned mana, unsigned health)
    : level(level),
      strength(strength),
      mana(mana),
      health(health)
{}

inline void Monster::takeDamage(unsigned damage)
{
    health -= damage - (damage * Monster::dmgReduction / 100);
}