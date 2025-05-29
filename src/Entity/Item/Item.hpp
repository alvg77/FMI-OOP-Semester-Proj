#ifndef ITEM_HPP
#define ITEM_HPP

#include <nlohmann/json_fwd.hpp>
#include <string>

#include "../NPEntity.hpp"
#include "ItemType.hpp"

class Item final : public NPEntity {
 public:
  Item(const std::string& name, double bonus, ItemType itemType);
  explicit Item(const nlohmann::json& itemJson);

  std::string getName() const;
  double getBonus() const;
  ItemType getItemType() const;

  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  Item* clone() const override;

  nlohmann::json toJson() const override;

  friend std::ostream& operator<<(std::ostream& os, const Item& item);

 private:
  std::string name;
  double bonus{};
  ItemType itemType;

  void loadJson(const nlohmann::json& itemJson);

  static constexpr char treasureSymbol = 'T';
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif  // ITEM_HPP
