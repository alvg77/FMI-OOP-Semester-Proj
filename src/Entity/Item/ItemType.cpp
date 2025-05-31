#include "ItemType.hpp"

std::string_view getItemTypeName(const ItemType itemType) {
  switch (itemType) {
    case ItemType::WEAPON:
      return "weapon";
    case ItemType::SPELL:
      return "spell";
    case ItemType::ARMOR:
      return "armor";
    default:
      return "[unknown type]";
  }
}

ItemType getItemType(const std::string& itemTypeStr) {
  if (itemTypeStr == "weapon") {
    return ItemType::WEAPON;
  }
  if (itemTypeStr == "spell") {
    return ItemType::SPELL;
  }
  if (itemTypeStr == "armor") {
    return ItemType::ARMOR;
  }
  throw std::invalid_argument("No such item type!");
}
