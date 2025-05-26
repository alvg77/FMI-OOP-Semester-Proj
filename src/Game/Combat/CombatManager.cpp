#include "CombatManager.hpp"

#include <iostream>
#include <random>

#include "../../Entity/Creature/Hero/Hero.hpp"
#include "../../Util/Util.hpp"

void CombatManager::initiateCombat(Hero& hero, Monster& monster) {
  Util::clearTerminal();

  std::cout << "Battle between " << hero.getName() << " and "
            << monster.getName() << " has started!" << std::endl;

  const CoinToss result = coinToss();
  bool heroTurn = (result == CoinToss::HEADS);

  std::cout << "\n" << (heroTurn ? "Hero" : "Monster") << " goes first!\n";

  while (hero.isAlive() && monster.isAlive()) {
    if (heroTurn) {
      std::cout << "\nHero makes an attack!" << std::endl;
      playerAttack(hero, monster);
    } else {
      std::cout << "\nMonster makes an attack!" << std::endl;
      monsterAttack(hero, monster);
    }

    std::cout << "Hero HP: " << hero.getCurrentHealth() << "/"
              << hero.getMaxHealth() << std::endl;
    std::cout << "Monster HP: " << monster.getCurrentHealth() << "/"
              << monster.getMaxHealth() << "\n" << std::endl;

    heroTurn = !heroTurn;
  }

  if (hero.isAlive()) {
    std::cout << hero.getName() << " has defeated " << monster.getName() << "!"
              << std::endl;
    hero.heal();
  } else {
    std::cout << monster.getName() << " has defeated " << hero.getName() << "!"
              << std::endl;
  }

  std::cout << "Press enter to continue...";
  std::cin.get();
}

CoinToss CombatManager::coinToss() {
  const unsigned int seed = time(nullptr);
  std::mt19937 rng(seed);
  std::uniform_int_distribution<unsigned> unif(0, 1000);

  const unsigned random = unif(rng);

  if (random % 2 == 0) {
    return CoinToss::HEADS;
  }
  return CoinToss::TAILS;
}

void CombatManager::playerAttack(const Hero& hero, Monster& monster) {
  std::cout << "<w> Weapon attack   <s> Spell attack" << std::endl;

  bool validChoice = true;
  do {
    char choice;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');

    switch (choice) {
      case 'w':
        hero.dealDamage(monster, AttackType::WEAPON);
        validChoice = true;
        break;
      case 's':
        hero.dealDamage(monster, AttackType::SPELL);
        validChoice = true;
        break;
      default:
        std::cout << "Invalid choice!" << std::endl;
        validChoice = false;
        break;
    }
  } while (!validChoice);
}

void CombatManager::monsterAttack(Hero& hero, const Monster& monster) {
  monster.dealDamage(hero);
}
