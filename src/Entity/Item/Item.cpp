#include "Item.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#include "../../Game/Interactions/InteractionsManager.hpp"

Item::Item(const std::string& name, const double bonus, const ItemType itemType)
    : name(name), bonus(bonus), itemType(itemType) {}

Item::Item(const nlohmann::json& itemJson) { loadJson(itemJson); }

std::string Item::getName() const { return name; }

double Item::getBonus() const { return bonus; }

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

NPEntity* Item::clone() const { return new Item(*this); }

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

  os << "<" << item.name << ", Mult: " << item.bonus << ", " << itemType << ">";
  return os;
}

nlohmann::json Item::toJson() const {
  using nlohmann::json;

  json itemJson;

  itemJson["name"] = name;
  itemJson["bonus"] = bonus;
  itemJson["itemtype"] = static_cast<unsigned>(itemType);

  return itemJson;
}

void Item::loadJson(const nlohmann::json& itemJson) {
  name = itemJson["name"].get<std::string>();
  bonus = itemJson["bonus"].get<double>();
  itemType = static_cast<ItemType>(itemJson["itemtype"].get<unsigned>());
}