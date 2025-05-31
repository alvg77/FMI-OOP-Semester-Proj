#include "ItemFactory.hpp"

#include <nlohmann/json.hpp>

#include "Item.hpp"
#include "ItemType.hpp"

NPEntity* ItemFactory::createItemFromJson(const nlohmann::json& itemJson) {
  const std::string name = itemJson["name"].get<std::string>();
  const double mult = itemJson["mult"].get<double>();

  if (mult < 0) {
    throw std::runtime_error("Invalid value for item bonus!");
  }

  const ItemType itemType = static_cast<ItemType>(itemJson["itemtype"].get<unsigned>()); // TODO: add a helper that does that

  return new Item(name, mult, itemType);
}
