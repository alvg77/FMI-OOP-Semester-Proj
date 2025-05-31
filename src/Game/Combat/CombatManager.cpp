#include "CombatManager.hpp"

#include <iostream>
#include <random>

#include "../../Hero/Hero.hpp"
#include "../../Util/Util.hpp"
#include "../Interactions/InteractionsManager.hpp"

void CombatManager::initiateCombat(Hero& hero, Monster& monster) {
  Util::clearTerminal();

  std::cout << "Battle begins!" << std::endl;

  const CoinToss result = coinToss();
  bool heroTurn = (result == CoinToss::HEADS);

  std::cout << "\n" << (heroTurn ? "Hero" : "Monster") << " goes first!\n";
  InteractionsManager::promptContinue();

  std::cout << "monster is alive " << monster.isAlive() << std::endl;
  std::cout << "hero is alive " << hero.isAlive() << std::endl;

  while (hero.isAlive() && monster.isAlive()) {
    Util::clearTerminal();

    if (heroTurn) {
      std::cout << "\nHero makes an attack!\n" << std::endl;
      hero.displayAttackDmg();
      playerAttack(hero, monster);
    } else {
      std::cout << "\nMonster makes an attack!" << std::endl;
      monsterAttack(hero, monster);
    }

    std::cout << "\n--------\n\n";
    std::cout << "Hero:" << std::endl;
    hero.displayStatus();
    std::cout << "\n--------\n\n";
    std::cout << "Monster:" << std::endl;
    monster.displayStatus();
    std::cout << "\n--------\n\n";

    heroTurn = !heroTurn;

    InteractionsManager::promptContinue();
  }

  Util::clearTerminal();

  if (hero.isAlive()) {
    std::cout << "You have defeated the enemy!" << std::endl;
    hero.heal();
  } else {
    std::cout << "You have been defeated in combat!" << std::endl;
  }
  InteractionsManager::promptContinue();
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
