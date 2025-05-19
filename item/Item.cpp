#include "Item.hpp"

std::ostream& operator<<(std::ostream& os, const ItemType& other) {
  switch (other) {
    case ItemType::WEAPON:
      os << "Weapon";
      break;
    case ItemType::SPELL:
      os << "Spell";
      break;
  }

  return os;
}

ItemType toItemType(const std::string& str) {
  std::string lower = str;
  std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](const unsigned char c){ return std::tolower(c); });

  if (str == "weapon") {
    return ItemType::WEAPON;
  }

  if (str == "spell") {
    return ItemType::SPELL;
  }

  throw std::invalid_argument("Cannot convert string to ItemType enum: " + str);
}


Item::Item(const std::string& name, const unsigned bonus,
           const ItemType itemType)
    : name(name), bonus(bonus), itemType(itemType) {}

std::ostream& operator<<(std::ostream& os, const Item& item) {
  os << item.name << ", Multiplier: " << item.bonus
     << ", Type: " << item.itemType;

  return os;
}
