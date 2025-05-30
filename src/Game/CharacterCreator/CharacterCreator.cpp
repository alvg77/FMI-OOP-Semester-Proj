#include "CharacterCreator.hpp"

#include <iostream>

#include "../../Entity/Creature/Hero/Hero.hpp"
#include "../../Entity/Creature/Hero/HeroFactory.hpp"
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
  const HeroRace heroRace = static_cast<HeroRace>(raceChoice - 1);

  std::cout << "Choose class:\n";
  std::cout << "1. Warrior\n2. Mage" << std::endl;
  std::cin >> classChoice;
  std::cin.ignore(1000, '\n');
  const HeroClass heroClass = static_cast<HeroClass>(classChoice - 1);

  Item* defaultArmor = new Item("Light Leather Armor", 0.05, ItemType::ARMOR);
  Item* defaultSpell = new Item("Firebolt", 0.1, ItemType::SPELL);
  Item* defaultWeapon = new Item("Iron Sword", 0.1, ItemType::WEAPON);

  return HeroFactory::createHero(name, 1, heroRace, heroClass, defaultWeapon,
                                 defaultSpell, defaultArmor);
}
