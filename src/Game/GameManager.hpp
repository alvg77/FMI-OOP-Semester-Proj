#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../Entity/Creature/Hero/Hero.hpp"
#include "../Map/Map.hpp"
#include "GameContext.hpp"

class Monster;
class Item;

class GameManager {
 public:
  GameManager();
  GameManager(const GameManager& other) = delete;
  GameManager& operator=(const GameManager& other) = delete;
  ~GameManager();

  void runGameLoop();

 private:
  static constexpr unsigned nlevels = 5;
  static const std::string saveFileLocation;

  unsigned level;
  GameContext ctx;
};

#endif  // GAMEMANAGER_HPP
