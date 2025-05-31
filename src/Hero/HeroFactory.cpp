#include "HeroFactory.hpp"

#include <nlohmann/json.hpp>

#include "../NPEntity/Item/Item.hpp"
#include "../NPEntity/Item/ItemFactory.hpp"
#include "../Stats/Stats.hpp"
#include "Hero.hpp"

Hero* HeroFactory::createHero(const std::string& name, const unsigned level,
                              const HeroRace heroRace,
                              const HeroClass heroClass, Item* weapon,
                              Item* spell, Item* armor) {
  const Stats stats = getInitialStats(heroClass) + getRacialBonus(heroRace);

  return new Hero(name, level, stats, stats.maxHealth, heroRace, heroClass,
                  weapon, spell, armor);
}

Hero* HeroFactory::createHeroFromJson(const nlohmann::json& heroJson) {
  using nlohmann::json;

  const std::string name = heroJson["name"].get<std::string>();
  const unsigned level = heroJson["level"].get<unsigned>();
  const HeroRace heroRace =
      static_cast<HeroRace>(heroJson["race"].get<unsigned>());
  const HeroClass heroClass =
      static_cast<HeroClass>(heroJson["class"].get<unsigned>());

  Stats stats{};
  stats.strength = heroJson["strength"].get<unsigned>();
  stats.mana = heroJson["mana"].get<unsigned>();
  stats.maxHealth = heroJson["maxhealth"].get<unsigned>();

  const double currentHealth = heroJson["currenthealth"].get<double>();

  if (currentHealth <= 0) {
    throw std::invalid_argument("Invalid value for 'currenthealth' in hero JSON");
  }

  json itemsJson = heroJson["items"];

  Item *armor = nullptr, *weapon = nullptr, *spell = nullptr;
  for (json& itemJson : itemsJson) {
    Item* item = dynamic_cast<Item*>(ItemFactory::createItemFromJson(itemJson));
    switch (item->getItemType()) {
      case ItemType::WEAPON:
        weapon = item;
        break;
      case ItemType::ARMOR:
        armor = item;
        break;
      case ItemType::SPELL:
        spell = item;
        break;
    }
  }

  return new Hero(name, level, stats, currentHealth, heroRace, heroClass, weapon, spell, armor);
}

Stats HeroFactory::getInitialStats(const HeroClass hClass) {
  switch (hClass) {
    case HeroClass::WARRIOR:
      return {20, 10, 40};
    case HeroClass::MAGE:
      return {10, 20, 40};
  }
  throw std::invalid_argument("Invalid hero class! Cannot assign initial stats!");
}

Stats HeroFactory::getRacialBonus(const HeroRace race) {
  switch (race) {
    case HeroRace::HUMAN:
      return {3, 2, 5};
    case HeroRace::ELF:
      return {0, 5, 10};
  }
  throw std::invalid_argument("Invalid hero race! Cannot assign racial bonus!");
}