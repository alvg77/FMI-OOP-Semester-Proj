#include "Wall.hpp"

#include <iostream>

bool Wall::onStep(Hero& hero) {
  std::cout << "You have encountered a wall!" << std::endl;
  return false;
}

void Wall::onInteract(Hero& hero) {}

char Wall::getSymbol() const { return Wall::wallSymbol; }

NPEntity* Wall::clone() const { return new Wall(*this); }
