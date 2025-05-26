#include "InteractionsManager.hpp"

#include <iostream>

#include "../../Entity/Creature/Hero/Hero.hpp"
#include "../../Entity/Item/Item.hpp"
#include "../../Util/Util.hpp"

void InteractionsManager::promptHeroItemEquip(Hero& hero, const Item* item) {
  Util::clearTerminal();

  char choice;

  std::cout << "You have found " << *item << ", "
            << getItemTypeName(item->getItemType()) << std::endl;

  std::cout << "Your current loadout:" << std::endl;
  hero.displayLoadout();

  std::cout << "Do you want to equip the item [y/n]:";
  std::cin >> choice;
  std::cin.ignore(1000, '\n');

  if (choice == 'y') {
    hero.equipItem(item);
  }
}

void InteractionsManager::promptHeroLevelUp(Hero& hero) {
  Util::clearTerminal();

  unsigned str, mn, hp;

  std::cout << "You have reached the end of the level! Level up your character!"
            << std::endl;
  std::cout << "Current stats: " << std::endl;
  std::cout << "Strength: " << hero.getStrength() << std::endl;
  std::cout << "Mana: " << hero.getMana() << std::endl;
  std::cout << "Max Health: " << hero.getMaxHealth() << std::endl;

  do {
    std::cout << "You have 30 points to allocate: " << std::endl;
    std::cout << "Enter points going to strength: ";
    std::cin >> str;
    std::cout << "Enter points going to mana: ";
    std::cin >> mn;
    std::cout << "Enter points going to max health: ";
    std::cin >> hp;
    std::cin.ignore(1000, '\n');
  } while (!hero.levelUp(hp, str, mn));
}

void InteractionsManager::promptContinue() {
  std::cout << "Press enter to continue...";
  std::cin.get();
}
