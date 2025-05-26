#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP

enum class ItemType { WEAPON, SPELL, ARMOR };

constexpr std::string_view getItemTypeName(ItemType itemType) {
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

constexpr ItemType getItemType(const std::string& itemTypeStr) {
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

#endif  // ITEMTYPE_HPP
