#include "GameManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "../Util/Util.hpp"
#include "CharacterCreator/CharacterCreator.hpp"
#include "Controls/ControlsManager.hpp"
#include "Interactions/InteractionsManager.hpp"
#include "Save/SaveManager.hpp"
#include "GameAction.hpp"

GameManager::GameManager() : level(1), ctx({nullptr, nullptr}) {}

const std::string GameManager::saveFileLocation = "../data/save/save.json";

GameManager::~GameManager() {
  delete ctx.hero;
  delete ctx.map;
}

void GameManager::runGameLoop() {
  std::cout << "1. New Game\n2. Load Game\n3. Exit Game" << std::endl;
  bool correctChoice = true;

  do {
    unsigned short choice;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');

    switch (choice) {
      case 1:
        level = 1;
        ctx.hero = CharacterCreator::createHero();
        ctx.map = new Map(level);
        correctChoice = true;
        break;
      case 2:
        try {
          ctx = SaveManager::loadGame();
          correctChoice = true;
        } catch (const std::exception& e) {
          std::cout << e.what() << std::endl;
          correctChoice = false;
        }
        break;
      default:
        correctChoice = false;
    }
  } while (!correctChoice);

  bool gameCompleted = false;
  while (!gameCompleted) {
    Util::clearTerminal();

    ctx.map->display();

    const GameAction action = ControlsManager::getInputs();

    if (action == GameAction::SAVE) {
      SaveManager::save(ctx);
      std::cout << "Game successfully saved!" << std::endl;
      InteractionsManager::promptContinue();
    } else if (action == GameAction::EXIT) {
      std::cout << "Exiting game" << std::endl;
      InteractionsManager::promptContinue();
      exit(0);
    } else {
      ctx.map->moveHero(*ctx.hero, action);
    }

    if (!ctx.hero->isAlive()) {
      std::cout << "\n\n===GAME OVER===" << std::endl;
      return;
    }

    if (ctx.map->hasReachedEnd()) {
      ++level;
      if (level > nlevels) {
        std::cout << "\n\n===GAME COMPLETED===\n" << std::endl;
        std::cout << "Thanks for playing!" << std::endl;
        gameCompleted = true;
      } else {
        Util::clearTerminal();
        InteractionsManager::promptHeroLevelUp(*ctx.hero);

        delete ctx.map;
        ctx.map = new Map(level);
      }
    }
  }
}
