#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "../NPEntity.hpp"
#include "ItemType.hpp"


class Item final : public NPEntity {
 public:
  Item(const std::string& name, double bonus, ItemType itemType);

  std::string getName() const;
  double getBonus() const;
  ItemType getItemType() const;

  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  NPEntity* clone() const override;

  friend std::ostream& operator<<(std::ostream& os, const Item& item);

 private:
  std::string name;
  double bonus;
  ItemType itemType;

  static constexpr char treasureSymbol = 'T';
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif  // ITEM_HPP
