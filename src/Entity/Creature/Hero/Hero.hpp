#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include <nlohmann/adl_serializer.hpp>

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
  explicit Hero(const nlohmann::json& heroJson);
  Hero(const Hero& other);
  Hero& operator=(const Hero& other);
  ~Hero() override;

  bool levelUp(const Stats& stats);

  void dealDamage(Monster& monster, AttackType attackType) const;
  void takeDamage(double damage) override;
  void heal();

  void equipItem(const Item* item);

  void displayLoadout(std::ostream& os = std::cout) const;

  nlohmann::json toJson() const override;

 private:
  HeroRace characterRace;
  HeroClass characterClass;

  Item* armor;
  Item* weapon;
  Item* spell;

  void loadJson(const nlohmann::json& heroJson) override;

  void swap(Hero& other) noexcept;

  static constexpr unsigned lvlUpPoints = 30;
};

#endif  // HERO_HPP
