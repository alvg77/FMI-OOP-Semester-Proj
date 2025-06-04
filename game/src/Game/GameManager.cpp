#include "GameManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "../Map/MapFactory.hpp"
#include "../Util/Util.hpp"
#include "CharacterCreator/CharacterCreator.hpp"
#include "Controls/ControlsManager.hpp"
#include "GameAction.hpp"
#include "Interactions/InteractionsManager.hpp"
#include "Save/SaveManager.hpp"

GameManager::GameManager() : level(1), ctx({nullptr, nullptr}) {}

const std::string GameManager::scoreFileLocation = "../../data/score/score.json";

GameManager::~GameManager() {
  delete ctx.hero;
  delete ctx.map;
}

void GameManager::runGameLoop() {
  bool correctChoice;

  do {
    std::cout << "1. New Game\n2. Load Game\n3. Leaderboard\n4. Exit Game"
              << std::endl;

    unsigned short choice;
    std::cin >> choice;
    std::cin.ignore(1000, '\n');

    switch (choice) {
      case 1:
        level = 1;
        ctx.hero = CharacterCreator::createHero();
        try {
          ctx.map = MapFactory::createMap(level);
        } catch (const std::exception& e) {
          std::cout
              << "Encountered an error while creating map! Exiting game..."
              << std::endl;
          std::cout << e.what() << std::endl;
          exit(0);
        }
        correctChoice = true;
        break;
      case 2:
        try {
          ctx = SaveManager::loadGame();
          correctChoice = true;
        } catch (const std::exception& e) {
          std::cout << "Encountered a problem with reading save file! Data "
                       "might be corrupted."
                    << std::endl;
          std::cout << e.what() << std::endl;
          InteractionsManager::promptContinue();
          correctChoice = false;
          Util::clearTerminal();
        }
        break;
      case 3:
        showLeaderboard();
        InteractionsManager::promptContinue();
        Util::clearTerminal();
        correctChoice = false;
        break;
      case 4:
        exit(0);
      default:
        correctChoice = false;
    }
  } while (!correctChoice);

  bool gameCompleted = false;
  while (!gameCompleted) {
    Util::clearTerminal();
    ctx.hero->displayScore();
    ctx.map->display();

    const GameAction action = ControlsManager::getInputs();

    if (action == GameAction::SAVE) {
      SaveManager::save(ctx);
      std::cout << "Game successfully saved!" << std::endl;
      InteractionsManager::promptContinue();
    } else if (action == GameAction::EXIT) {
      SaveManager::save(ctx);
      std::cout << "Exiting game. Progress saved." << std::endl;
      InteractionsManager::promptContinue();
      exit(0);
    } else {
      ctx.map->moveHero(*ctx.hero, action);
    }

    if (!ctx.hero->isAlive()) {
      std::cout << "\n\n===GAME OVER===" << std::endl;
      ctx.hero->saveScore(scoreFileLocation);
      return;
    }

    if (ctx.map->hasReachedEnd()) {
      ++level;
      if (level > nlevels) {
        std::cout << "\n\n===GAME COMPLETED===\n" << std::endl;
        std::cout << "Thanks for playing!" << std::endl;
        ctx.hero->saveScore(scoreFileLocation);
        gameCompleted = true;
      } else {
        Util::clearTerminal();
        InteractionsManager::promptHeroLevelUp(*ctx.hero);

        delete ctx.map;
        ctx.map = MapFactory::createMap(level);

        SaveManager::save(ctx);
      }
    }
  }
}

void GameManager::showLeaderboard(std::ostream& os) {
  using nlohmann::json;

  Util::clearTerminal();

  std::ifstream ifs (GameManager::scoreFileLocation);
  if (!ifs.is_open()) {
    std::cout << "Leaderboard is empty!" << std::endl;
    return;
  }

  json leaderboard;
  ifs >> leaderboard;

  const std::vector<json> scoresData = leaderboard["leaderboard"].get<std::vector<json>>();

  if (scoresData.empty()) {
    std::cout << "Leaderboard is empty!" << std::endl;
    return;
  }

  for (const json& scoreData : scoresData) {
    os << "---------------" << std::endl;
    os << "Player: " <<  scoreData["playername"].get<std::string>() << std::endl;
    os << "Score: " << scoreData["score"].get<unsigned>() << std::endl;
    os << "---------------" << std::endl;
  }

  ifs.close();
}
