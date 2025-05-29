#include "Hero.hpp"

#include <nlohmann/json.hpp>

#include "../../Item/Item.hpp"
#include "../Monster/Monster.hpp"

Hero::Hero(const std::string& name, const unsigned level, const Stats& stats,
           const HeroRace characterRace, const HeroClass characterClass,
           Item* weapon, Item* spell, Item* armor)
    : Creature(name, level, stats),
      characterRace(characterRace),
      characterClass(characterClass),
      armor(nullptr),
      weapon(nullptr),
      spell(nullptr) {
  equipItem(weapon);
  equipItem(spell);
  equipItem(armor);
}

Hero::Hero(const nlohmann::json& heroJson)
    : Creature(heroJson), armor(nullptr), weapon(nullptr), spell(nullptr) {
  loadJson(heroJson);
}

Hero::Hero(const Hero& other)
    : Creature(other),
      characterRace(other.characterRace),
      characterClass(other.characterClass),
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

bool Hero::levelUp(const Stats& stats) {
  if (stats.mana + stats.strength + stats.maxHealth != lvlUpPoints) {
    return false;
  }

  increaseStats(stats);
  increaseCurrentHealth(getMaxHealth() - getCurrentHealth());

  return true;
}

void Hero::dealDamage(Monster& monster, const AttackType attackType) const {
  switch (attackType) {
    case AttackType::WEAPON: {
      double weaponDamage = getStrength();
      if (weapon != nullptr) {
        weaponDamage += weapon->getBonus() * weaponDamage;
      }
      monster.takeDamage(weaponDamage);
      break;
    }
    case AttackType::SPELL: {
      double spellDamage = getMana();
      if (spell != nullptr) {
        spellDamage += spell->getBonus() * spellDamage;
      }
      monster.takeDamage(spellDamage);
      break;
    }
  }
}

void Hero::takeDamage(double damage) {
  if (armor != nullptr) {
    damage -= armor->getBonus() * damage;
  }
  reduceCurrentHealth(damage);
}

void Hero::heal() {
  if (getCurrentHealth() < static_cast<double>(getMaxHealth()) / 2) {
    Creature::increaseCurrentHealth(static_cast<double>(getMaxHealth()) / 2 -
                                    getCurrentHealth());
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

void Hero::displayLoadout(std::ostream& os) const {
  if (armor != nullptr) {
    os << *armor << std::endl;
  } else {
    os << "No armor equipped." << std::endl;
  }

  if (weapon != nullptr) {
    os << *weapon << std::endl;
  } else {
    os << "No weapon equipped." << std::endl;
  }

  if (spell != nullptr) {
    os << *spell << std::endl;
  } else {
    os << "No spell equipped." << std::endl;
  }
}

nlohmann::json Hero::toJson() const {
  using nlohmann::json;

  json heroJson = Creature::toJson();

  heroJson["race"] = characterRace;
  heroJson["class"] = characterClass;

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

void Hero::loadJson(const nlohmann::json& heroJson) {
  using nlohmann::json;

  characterRace = static_cast<HeroRace>(heroJson["race"].get<unsigned>());
  characterClass = static_cast<HeroClass>(heroJson["class"].get<unsigned>());

  for (const json& itemData : heroJson["items"]) {
    Item* item = new Item(itemData);
    equipItem(item);
  }
}

void Hero::swap(Hero& other) noexcept {
  Creature::swap(other);

  using std::swap;

  swap(characterRace, other.characterRace);
  swap(characterClass, other.characterClass);
  swap(armor, other.armor);
  swap(weapon, other.weapon);
  swap(spell, other.spell);
}
