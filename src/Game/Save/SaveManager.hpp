#ifndef SAVEMANAGER_HPP
#define SAVEMANAGER_HPP

#include <nlohmann/json_fwd.hpp>
#include <string>

struct GameContext;
class Map;
class Hero;

class SaveManager {
 public:
  static void save(const GameContext& ctx);
  static GameContext loadGame();

 private:
  static const std::string saveFileLoc;
};

#endif  // SAVEMANAGER_HPP
