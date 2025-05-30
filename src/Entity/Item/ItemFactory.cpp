#include "ItemFactory.hpp"

#include <nlohmann/json.hpp>

#include "Item.hpp"
#include "ItemType.hpp"

NPEntity* ItemFactory::createItemFromJson(const nlohmann::json& itemJson) {
  const std::string name = itemJson["name"].get<std::string>();
  const double bonus = itemJson["bonus"].get<double>();
  const ItemType itemType = static_cast<ItemType>(itemJson["itemtype"].get<unsigned>());

  return new Item(name, bonus, itemType);
}
