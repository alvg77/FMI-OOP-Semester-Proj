#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <iostream>
#include <nlohmann/json_fwd.hpp>

#include "../../NPEntity.hpp"
#include "../Stats.hpp"

class Monster final : public NPEntity {
 public:
  Monster(const std::string& name, unsigned level, const Stats& stats, double scalesDefenceMult);

  void dealDamage(Hero& hero) const;
  void takeDamage(double damage);

  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  Monster* clone() const override;

  bool isAlive() const;

  void displayStatus(std::ostream& os = std::cout) const;

  nlohmann::json toJson() const override;

 private:
  std::string name;
  unsigned level;
  Stats stats;
  double scalesDefenceMult;
  double currentHealth;
  static constexpr char monsterSymbol = 'M';
};

#endif  // MONSTER_HPP
