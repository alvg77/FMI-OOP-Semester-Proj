#ifndef LEVELLOADER_HPP
#define LEVELLOADER_HPP

#include <nlohmann/json.hpp>
#include <vector>

struct LoadedLevel;

class Cell;
class Item;
class Monster;
struct Stats;

using nlohmann::json;

class LevelLoader {
 public:
  static LoadedLevel load(unsigned n);

 private:
  static void validateLevelJson(const json& data);
  static json readJson(const std::string& path);
  static void parseGrid(const json& jsonGrid,
                        std::vector<std::vector<Cell*>>& grid,
                        std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
                        unsigned cols);
  static std::vector<Item*> loadItems(const json& treasurePool, unsigned n);
  static std::vector<Monster*> loadMonsters(unsigned count, unsigned n);

  static const std::string levelFileLocation;
  static const std::string monstersFileLocation;
};

#endif  // LEVELLOADER_HPP
