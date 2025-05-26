#include "GameManager.hpp"

#include "../Util/Util.hpp"
#include "CharacterCreator/CharacterCreator.hpp"
#include "Controls/ControlsManager.hpp"
#include "Interactions/InteractionsManager.hpp"

GameManager::GameManager() : level(1), hero(nullptr), map(nullptr) {}

const std::string GameManager::saveFileLocation = "../data/save/save.json";

GameManager::~GameManager() {
  delete hero;
  delete map;
}

void GameManager::runGameLoop() {
  std::cout << "1. New Game\n2. Load Game\n3. Exit Game" << std::endl;
  bool correctChoice = true;
  unsigned short choice;
  std::cin >> choice;
  std::cin.ignore(1000, '\n');

  do {
    switch (choice) {
      case 1:
        level = 1;
        hero = CharacterCreator::createHero();
        map = new Map(level);
        break;
      case 2:
        loadGame();
        break;
      default:
        correctChoice = false;
    }
  } while (!correctChoice);

  bool gameCompleted = false;
  while (!gameCompleted) {
    Util::clearTerminal();

    map->display();
    map->moveHero(*hero, ControlsManager::getMovementInputs());

    if (!hero->isAlive()) {
      std::cout << "\n\n===GAME OVER===" << std::endl;
      return;
    }

    if (map->hasReachedEnd()) {
      ++level;
      if (level > nlevels) {
        std::cout << "\n\n===GAME COMPLETED===\n" << std::endl;
        std::cout << "Thanks for playing!" << std::endl;
        gameCompleted = true;
      } else {
        Util::clearTerminal();
        InteractionsManager::promptHeroLevelUp(*hero);

        delete map;
        map = new Map(level);
      }
    }
  }
}

void GameManager::saveGame() {}

void GameManager::loadGame() {}
