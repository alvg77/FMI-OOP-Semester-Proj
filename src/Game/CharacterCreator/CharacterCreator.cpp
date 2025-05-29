#include "CharacterCreator.hpp"

#include <iostream>

#include "../../Entity/Creature/Hero/Hero.hpp"
#include "../../Entity/Item/Item.hpp"
#include "../../Entity/Item/ItemType.hpp"

Hero* CharacterCreator::createHero() {
  std::string name;
  int raceChoice, classChoice;

  std::cout << "Enter hero name: ";
  std::getline(std::cin, name);

  std::cout << "Choose race:\n";
  std::cout << "1. Human\n2. Elf" << std::endl;
  std::cin >> raceChoice;
  std::cin.ignore(1000, '\n');
  const HeroRace race = static_cast<HeroRace>(raceChoice - 1);

  std::cout << "Choose class:\n";
  std::cout << "1. Warrior\n2. Mage" << std::endl;
  std::cin >> classChoice;
  std::cin.ignore(1000, '\n');
  const HeroClass heroClass = static_cast<HeroClass>(classChoice - 1);

  const Stats initialStats = getInitialStats(heroClass);
  const Stats racialBonus = getRacialBonus(race);
  const Stats finalStats = initialStats + racialBonus;

  const Item defaultArmor("Light Leather Armor", 0.05, ItemType::ARMOR);
  const Item defaultSpell("Firebolt", 0.1, ItemType::SPELL);
  const Item defaultWeapon("Iron Sword", 0.1, ItemType::WEAPON);

  return new Hero(name,          1,
                  finalStats,    race,
                  heroClass,     &defaultWeapon,
                  &defaultSpell, &defaultArmor);
}

Stats CharacterCreator::getInitialStats(const HeroClass hClass) {
  switch (hClass) {
    case HeroClass::WARRIOR:
      return {20, 10, 40};
    case HeroClass::MAGE:
      return {10, 20, 40};
  }
}

Stats CharacterCreator::getRacialBonus(HeroRace race) {
  switch (race) {
    case HeroRace::HUMAN:
      return {3, 2, 5};
    case HeroRace::ELF:
      return {0, 5, 10};
  }
}
