#include "Wall.hpp"

#include <iostream>

#include "../../Game/Interactions/InteractionsManager.hpp"

bool Wall::onStep(Hero& hero) {
  std::cout << "You have encountered a wall!" << std::endl;
  InteractionsManager::promptContinue();

  return false;
}

void Wall::onInteract(Hero& hero) {}

char Wall::getSymbol() const { return Wall::wallSymbol; }

Wall* Wall::clone() const { return new Wall(*this); }
