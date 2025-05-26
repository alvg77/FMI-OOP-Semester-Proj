#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "../../NPEntity.hpp"
#include "../Creature.hpp"

class Monster final : public Creature, public NPEntity {
 public:
  Monster(const std::string& name, unsigned level, Stats stats);

  void dealDamage(Hero& hero) const;
  void takeDamage(double damage) override;

  void levelUp();

  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  NPEntity* clone() const override;

 private:
  double scalesDefenceMult{};
  static constexpr char monsterSymbol = 'M';
};

#endif  // MONSTER_HPP
