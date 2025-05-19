#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>

enum class ItemType {
  WEAPON,
  SPELL
};

std::ostream& operator<<(std::ostream& os, const ItemType& other);
ItemType toItemType(const std::string& str);

struct Item {
  std::string name;
  unsigned bonus;
  ItemType itemType;

  Item(const std::string& name, unsigned bonus, ItemType itemType);
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif  // ITEM_HPP
