#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <nlohmann/json_fwd.hpp>

#include "../../NPEntity.hpp"
#include "../Creature.hpp"

class Monster final : public Creature, public NPEntity {
 public:
  Monster(const std::string& name, unsigned level, Stats initialStats);
  explicit Monster(const nlohmann::json& monsterJson);

  void dealDamage(Hero& hero) const;
  void takeDamage(double damage) override;

  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  Monster* clone() const override;

  nlohmann::json toJson() const override;

 private:
  double scalesDefenceMult{};
  static constexpr char monsterSymbol = 'M';

  void loadJson(const nlohmann::json& monsterJson) override;
};

#endif  // MONSTER_HPP
