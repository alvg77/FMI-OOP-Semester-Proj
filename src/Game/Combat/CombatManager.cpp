#include "CombatManager.hpp"

#include <iostream>
#include <random>

#include "../../Entity/Creature/Hero/Hero.hpp"

void CombatManager::initiateCombat(Hero& hero, Monster& monster) {
  std::cout << "Battle between " << hero.getName() << " and "
            << monster.getName() << " has started!" << std::endl;

  const CoinToss result = coinToss();
  bool heroTurn = (result == CoinToss::HEADS);

  std::cout << (heroTurn ? "Hero" : "Monster") << " goes first!\n";

  while (hero.isAlive() && monster.isAlive()) {
    if (heroTurn) {
      playerAttack(hero, monster);
    } else {
      monsterAttack(hero, monster);
    }

    std::cout << "Hero HP: " << hero.getCurrentHealth() << std::endl;
    std::cout << "Monster HP: " << monster.getCurrentHealth() << std::endl;

    heroTurn = !heroTurn;
  }

  if (hero.isAlive()) {
    std::cout << hero.getName() << " has defeated " << monster.getName() << "!"
              << std::endl;
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
