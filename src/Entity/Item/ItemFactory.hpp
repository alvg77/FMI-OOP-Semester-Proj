#ifndef ITEMFACTORY_HPP
#define ITEMFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class NPEntity;
class Item;

class ItemFactory {
 public:
  static NPEntity* createItemFromJson(const nlohmann::json& itemJson);
};

#endif  // ITEMFACTORY_HPP
