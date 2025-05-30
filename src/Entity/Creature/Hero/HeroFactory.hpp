#ifndef HEROFACTORY_HPP
#define HEROFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

#include "Class/HeroClass.hpp"
#include "Race/HeroRace.hpp"

class Item;
enum class HeroRace;
struct Stats;
class Hero;

class HeroFactory {
 public:
  static Hero* createHero(const std::string& name, unsigned level,
                          HeroRace heroRace, HeroClass heroClass, Item* weapon,
                          Item* spell, Item* armor);

  static Hero* createHeroFromJson(const nlohmann::json& heroJson);

 private:
  static Stats getInitialStats(HeroClass hClass);

  static Stats getRacialBonus(HeroRace race);

};

#endif  // HEROFACTORY_HPP
