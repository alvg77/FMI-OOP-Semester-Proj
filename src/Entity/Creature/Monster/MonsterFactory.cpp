#include "MonsterFactory.hpp"

#include <nlohmann/json.hpp>

#include "../Stats.hpp"
#include "Monster.hpp"

Monster* MonsterFactory::createMonster(const std::string& name,
                                       const unsigned level,
                                       const Stats& stats) {
  return new Monster(name, level, stats,
                     MonsterFactory::scalesDefenceMult +
                         (level - 1) * MonsterFactory::scalesDefLvlUpBonus);
}

NPEntity* MonsterFactory::createMonsterFromJson(
    const nlohmann::json& monsterJson) {
  using nlohmann::json;

  const std::string name = monsterJson["name"].get<std::string>();
  const unsigned level = monsterJson["level"].get<unsigned>();
  const double scalesDefenceMult =
      monsterJson["scalesdefencemult"].get<double>();

  Stats stats{};
  stats.strength = monsterJson["strength"].get<unsigned>();
  stats.mana = monsterJson["mana"].get<unsigned>();
  stats.maxHealth = monsterJson["maxhealth"].get<unsigned>();

  return new Monster(name, level, stats, scalesDefenceMult);
}
