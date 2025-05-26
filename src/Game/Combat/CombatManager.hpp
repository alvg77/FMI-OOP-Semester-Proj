#ifndef COMBATMANAGER_HPP
#define COMBATMANAGER_HPP

#include "../../Entity/Creature/Monster/Monster.hpp"
#include "CoinToss.hpp"

class Monster;
class Hero;

class CombatManager {
public:
  static void initiateCombat(Hero& hero, Monster& monster);
private:
  static CoinToss coinToss();
  static void playerAttack(const Hero& hero, Monster& monster);
  static void monsterAttack(Hero& hero, const Monster& monster);
};

#endif //COMBATMANAGER_HPP
