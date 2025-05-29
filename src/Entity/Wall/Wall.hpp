#ifndef WALL_HPP
#define WALL_HPP

#include "../NPEntity.hpp"

class Wall final : public NPEntity {
 public:
  bool onStep(Hero& hero) override;
  void onInteract(Hero& hero) override;
  char getSymbol() const override;
  Wall* clone() const override;
 private:
  static constexpr char wallSymbol = '#';
};

#endif  // WALL_HPP
