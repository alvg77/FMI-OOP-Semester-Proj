#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>

#include "../../../Game/Combat/AttackType.hpp"
#include "../Creature.hpp"
#include "Class/HeroClass.hpp"
#include "Race/HeroRace.hpp"

class Monster;
class Item;

class Hero final : public Creature {
 public:
  Hero(const std::string& name, unsigned level, const Stats& stats,
       HeroRace characterRace, HeroClass characterClass, const Item* weapon,
       const Item* spell, const Item* armor);
  Hero(const Hero& other);
  Hero& operator=(const Hero& other);
  ~Hero() override;

  void dealDamage(Monster& monster, AttackType attackType) const;
  void takeDamage(double damage) override;
  void heal();

  void equipItem(const Item* item);

  void displayLoadout(std::ostream& os = std::cout) const;

 private:
  HeroRace characterRace;
  HeroClass characterClass;

  Item* armor;
  Item* weapon;
  Item* spell;

  void swap(Hero& other) noexcept;
};

#endif  // HERO_HPP
