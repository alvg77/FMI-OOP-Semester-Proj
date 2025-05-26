#include "Item.hpp"

#include <iostream>

#include "../../Game/Interactions/InteractionsManager.hpp"

Item::Item(const std::string& name, const double bonus, const ItemType itemType)
    : name(name), bonus(bonus), itemType(itemType) {}


std::string Item::getName() const { return name; }

double Item::getBonus() const { return bonus; }

ItemType Item::getItemType() const { return itemType; }

bool Item::onStep(Hero& hero) {
  std::cout << *this << std::endl;
  return true;
}

void Item::onInteract(Hero& hero) {
  InteractionsManager::promptHeroItemEquip(hero, this);
  status = NPEntityStatus::INACTIVE;
}

char Item::getSymbol() const { return Item::treasureSymbol; }


NPEntity* Item::clone() const {
  return new Item(*this);
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
  std::string itemType;

  switch (item.itemType) {
    case ItemType::WEAPON:
      itemType = "Weapon";
      break;
    case ItemType::SPELL:
      itemType = "Spell";
      break;
    default:
      itemType = "";
  }

  os << "<" << item.name << ", Mult: " << item.bonus << ", " << itemType << ">";
  return os;
}
