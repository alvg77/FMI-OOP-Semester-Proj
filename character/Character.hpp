#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <string>

#include "CharacterClass.hpp"
#include "CharacterRace.hpp"

class Monster;
class Item;

class Character {
 public:
  enum class AttackType { WEAPON, SPELL };

  Character(std::string name, CharacterRace r, CharacterClass c);

  Character(const Character &other);

  Character &operator=(const Character &other);

  void takeDamage(unsigned amount);

  void printStats(std::ostream &os = std::cout) const;

  friend void swap(Character &a, Character &b) noexcept;

  ~Character();

  void levelUp(unsigned str, unsigned mn, unsigned hp);

  void dealDamage(Monster &monster, AttackType attackType) const;

 private:
  std::string characterName;
  unsigned strength;
  unsigned mana;
  double health;
  unsigned maxHealth;
  unsigned level;
  unsigned attrPoints;
  CharacterRace characterRace;
  CharacterClass characterClass;

  Item *armor;
  Item *weapon;
  Item *spell;

  void setInitialStats();

  void applyRacialBonus();

  void addStartingLoadout();

  static void printEquippedItem(std::ostream &os, const Item *item);

  void distributePoints(unsigned str, unsigned mn, unsigned hp);
};

void swap(Character &a, Character &b) noexcept;

#endif  // CHARACTER_HPP
