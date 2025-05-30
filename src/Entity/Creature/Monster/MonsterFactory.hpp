#ifndef MONSTERFACTORY_HPP
#define MONSTERFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class NPEntity;
struct Stats;
class Monster;

class MonsterFactory {
 public:
  static Monster* createMonster(const std::string& name, unsigned level,
                                const Stats& stats);
  static NPEntity* createMonsterFromJson(const nlohmann::json& monsterJson);
 private:
  static constexpr double scalesDefenceMult = 0.15;
  static constexpr double scalesDefLvlUpBonus = 0.05;
};

#endif  // MONSTERFACTORY_HPP
