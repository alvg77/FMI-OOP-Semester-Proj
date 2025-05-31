#include "Hero.hpp"

#include <nlohmann/json.hpp>

#include "../NPEntity/Item/Item.hpp"
#include "../NPEntity/Monster/Monster.hpp"

Hero::Hero(const std::string& name, const unsigned level, const Stats& stats,
           const double currentHealth, const HeroRace heroRace,
           const HeroClass heroClass, Item* weapon, Item* spell, Item* armor)
    : name(name),
      level(level),
      stats(stats),
      currentHealth(currentHealth),
      heroRace(heroRace),
      heroClass(heroClass),
      armor(armor),
      weapon(weapon),
      spell(spell) {}

Hero::Hero(const Hero& other)
    : name(other.name),
      level(other.level),
      stats(other.stats),
      currentHealth(other.currentHealth),
      heroRace(other.heroRace),
      heroClass(other.heroClass),
      armor(nullptr),
      weapon(nullptr),
      spell(nullptr) {
  if (other.armor != nullptr) {
    armor = other.armor->clone();
  }
  if (other.weapon != nullptr) {
    weapon = other.weapon->clone();
  }
  if (other.spell != nullptr) {
    spell = other.spell->clone();
  }
}

Hero& Hero::operator=(const Hero& other) {
  if (this != &other) {
    Hero temp(other);
    swap(temp);
  }

  return *this;
}

Hero::~Hero() {
  delete armor;
  delete weapon;
  delete spell;
}

bool Hero::levelUp(const Stats& incrementStats) {
  if (incrementStats.mana + incrementStats.strength +
          incrementStats.maxHealth !=
      lvlUpPoints) {
    return false;
  }

  ++level;
  stats = stats + incrementStats;
  currentHealth = stats.maxHealth;

  return true;
}

void Hero::dealDamage(Monster& monster, const AttackType attackType) const {
  switch (attackType) {
    case AttackType::WEAPON: {
      double weaponDamage = stats.strength;
      if (weapon != nullptr) {
        weaponDamage += weapon->getMult() * weaponDamage;
      }
      monster.takeDamage(weaponDamage);
      break;
    }
    case AttackType::SPELL: {
      double spellDamage = stats.mana;
      if (spell != nullptr) {
        spellDamage += spell->getMult() * spellDamage;
      }
      monster.takeDamage(spellDamage);
      break;
    }
  }
}

void Hero::takeDamage(double damage) {
  if (armor != nullptr) {
    damage -= armor->getMult() * damage;
  }
  currentHealth -= damage;
}

void Hero::heal() {
  if (currentHealth < static_cast<double>(stats.maxHealth) / 2) {
    currentHealth = static_cast<double>(stats.maxHealth) / 2;
  }
}

void Hero::equipItem(Item* item) {
  if (item == nullptr) {
    return;
  }

  switch (item->getItemType()) {
    case ItemType::ARMOR:
      delete armor;
      armor = item;
      break;
    case ItemType::WEAPON:
      delete weapon;
      weapon = item;
      break;
    case ItemType::SPELL:
      delete spell;
      spell = item;
      break;
  }
}

bool Hero::isAlive() const { return currentHealth > 0; }

void Hero::displayStats(std::ostream& os) const {
  os << "str: " << stats.strength << ", mana: " << stats.mana
     << ", max health: " << stats.maxHealth << std::endl;
}

void Hero::displayAttackDmg(std::ostream& os) const {
  std::cout << "Weapon attack damage: "
            << (weapon != nullptr ? stats.strength * (1 + weapon->getMult())
                                  : stats.strength)
            << std::endl;

  std::cout << "Spell attack damage: "
            << (spell != nullptr ? stats.mana * (1 + spell->getMult())
                                 : stats.mana)
            << std::endl;
}

void Hero::displayStatus(std::ostream& os) const {
  os << name << ": " << (currentHealth >= 0 ? currentHealth : 0) << "/"
     << stats.maxHealth << std::endl;
  os << "Resistence: " << (armor != nullptr ? armor->getMult() : 0)
     << std::endl;
}

void Hero::displayLoadout(std::ostream& os) const {
  if (armor != nullptr) {
    os << *armor << std::endl;
  } else {
    os << "No armor equipped." << std::endl;
  }

  if (weapon != nullptr) {
    os << *weapon << std::endl;
    os << "Weapon damage: " << stats.strength * (1 + weapon->getMult())
       << std::endl;
  } else {
    os << "No weapon equipped." << std::endl;
  }

  if (spell != nullptr) {
    os << *spell << std::endl;
    os << "Spell damage: " << stats.mana * (1 + spell->getMult()) << std::endl;
  } else {
    os << "No spell equipped." << std::endl;
  }
}

nlohmann::json Hero::toJson() const {
  using nlohmann::json;

  json heroJson;

  heroJson["name"] = name;
  heroJson["level"] = level;
  heroJson["strength"] = stats.strength;
  heroJson["mana"] = stats.mana;
  heroJson["maxhealth"] = stats.maxHealth;
  heroJson["currenthealth"] = currentHealth;
  heroJson["race"] = heroRace;
  heroJson["class"] = heroClass;

  std::vector<json> itemsJson;

  if (armor != nullptr) {
    itemsJson.push_back(armor->toJson());
  }

  if (weapon != nullptr) {
    itemsJson.push_back(weapon->toJson());
  }

  if (spell != nullptr) {
    itemsJson.push_back(spell->toJson());
  }

  heroJson["items"] = itemsJson;

  return heroJson;
}

void Hero::swap(Hero& other) noexcept {
  using std::swap;

  swap(name, other.name);
  swap(level, other.level);
  swap(stats, other.stats);
  swap(currentHealth, other.currentHealth);
  swap(heroRace, other.heroRace);
  swap(heroClass, other.heroClass);
  swap(armor, other.armor);
  swap(weapon, other.weapon);
  swap(spell, other.spell);
}
