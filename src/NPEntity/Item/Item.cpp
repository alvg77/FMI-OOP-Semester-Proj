#include "Item.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#include "../../Game/Interactions/InteractionsManager.hpp"

Item::Item(const std::string& name, const double mult, const ItemType itemType)
    : name(name), mult(mult), itemType(itemType) {}

std::string Item::getName() const { return name; }

double Item::getMult() const { return mult; }

ItemType Item::getItemType() const { return itemType; }

bool Item::onStep(Hero& hero) {
  std::cout << *this << std::endl;
  InteractionsManager::promptContinue();

  return true;
}

void Item::onInteract(Hero& hero) {
  InteractionsManager::promptHeroItemEquip(hero, this);
  status = NPEntityStatus::INACTIVE;
}

char Item::getSymbol() const { return Item::treasureSymbol; }

Item* Item::clone() const { return new Item(*this); }

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
      itemType = "Armor";
  }

  os << "<" << item.name << ", Mult: " << item.mult << ", " << itemType << ">";
  return os;
}

nlohmann::json Item::toJson() const {
  using nlohmann::json;

  json itemJson;

  itemJson["name"] = name;
  itemJson["mult"] = mult;
  itemJson["itemtype"] = getItemTypeName(itemType);

  return itemJson;
}