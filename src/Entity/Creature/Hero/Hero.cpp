#include "Hero.hpp"

#include "../../Item/Item.hpp"
#include "../Monster/Monster.hpp"

Hero::Hero(const std::string& name, const unsigned level, const Stats& stats,
           const HeroRace characterRace, const HeroClass characterClass,
           const Item* weapon, const Item* spell, const Item* armor)
    : Creature(name, level, stats, 30),
      characterRace(characterRace),
      characterClass(characterClass),
      armor(nullptr),
      weapon(nullptr),
      spell(nullptr) {
  if (armor != nullptr) {
    this->armor = dynamic_cast<Item*>(armor->clone());
  }
  if (weapon != nullptr) {
    this->weapon = dynamic_cast<Item*>(weapon->clone());
  }
  if (spell != nullptr) {
    this->spell = dynamic_cast<Item*>(spell->clone());
  }
}

Hero::Hero(const Hero& other)
    : Creature(other),
      characterRace(other.characterRace),
      characterClass(other.characterClass),
      armor(nullptr),
      weapon(nullptr),
      spell(nullptr) {
  if (other.armor != nullptr) {
    armor = dynamic_cast<Item*>(other.armor->clone());
  }
  if (other.weapon != nullptr) {
    weapon = dynamic_cast<Item*>(other.weapon->clone());
  }
  if (other.spell != nullptr) {
    spell = dynamic_cast<Item*>(other.spell->clone());
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
    Creature::increaseCurrentHealth(static_cast<double>(getMaxHealth()) / 2);
  }
}

void Hero::equipItem(const Item* item) {
  if (item == nullptr) {
    return;
  }

  switch (item->getItemType()) {
    case ItemType::ARMOR:
      delete armor;
      armor = dynamic_cast<Item*>(item->clone());
      break;
    case ItemType::WEAPON:
      delete weapon;
      armor = dynamic_cast<Item*>(item->clone());
      break;
    case ItemType::SPELL:
      delete spell;
      armor = dynamic_cast<Item*>(item->clone());
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

void Hero::swap(Hero& other) noexcept {
  Creature::swap(other);

  using std::swap;

  swap(characterRace, other.characterRace);
  swap(characterClass, other.characterClass);
  swap(armor, other.armor);
  swap(weapon, other.weapon);
  swap(spell, other.spell);
}
