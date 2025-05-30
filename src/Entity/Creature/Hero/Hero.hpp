#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include <nlohmann/adl_serializer.hpp>

#include "../../../Game/Combat/AttackType.hpp"
#include "../Stats.hpp"
#include "Class/HeroClass.hpp"
#include "Race/HeroRace.hpp"

class Monster;
class Item;
struct Stats;

class Hero {
 public:
  Hero(const std::string& name, unsigned level, const Stats& stats,
       double currentHealth, HeroRace heroRace, HeroClass heroClass,
       Item* weapon, Item* spell, Item* armor);
  Hero(const Hero& other);
  Hero& operator=(const Hero& other);
  ~Hero();

  bool levelUp(const Stats& incrementStats);

  void dealDamage(Monster& monster, AttackType attackType) const;
  void takeDamage(double damage);
  void heal();

  void equipItem(Item* item);

  bool isAlive() const;

  void displayStats(std::ostream& os = std::cout) const;
  void displayAttackDmg(std::ostream& os = std::cout) const;
  void displayStatus(std::ostream& os = std::cout) const;
  void displayLoadout(std::ostream& os = std::cout) const;

  nlohmann::json toJson() const;

 private:
  std::string name;
  unsigned level;
  Stats stats;
  double currentHealth;
  HeroRace heroRace;
  HeroClass heroClass;

  Item* armor;
  Item* weapon;
  Item* spell;

  void swap(Hero& other) noexcept;

  static constexpr unsigned lvlUpPoints = 30;
};

#endif  // HERO_HPP
