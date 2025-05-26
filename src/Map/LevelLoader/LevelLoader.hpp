#ifndef LEVELLOADER_HPP
#define LEVELLOADER_HPP

#include <nlohmann/json.hpp>
#include <vector>

class Cell;
class Item;
class Monster;
struct Stats;

using nlohmann::json;

class LevelLoader {
 public:
  struct LoadedLevel {
    unsigned rows;
    unsigned cols;
    unsigned monsterN;
    unsigned treasureN;
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::pair<unsigned, unsigned>> freeSpaces;
    std::vector<Item*> items;
    std::vector<Monster*> monsters;
  };

  static LoadedLevel load(const std::string& path,
                          const std::string& monstersPath);

 private:
  static void validateLevelJson(const json& data);
  static json readJson(const std::string& path);
  static void parseGrid(const json& json, std::vector<std::vector<Cell*>>& grid,
                        std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
                        unsigned cols);
  static std::vector<Item*> loadItems(const json& treasurePool, unsigned n);
  static std::vector<Monster*> loadMonsters(const std::string& path,
                                            unsigned count);
};

#endif  // LEVELLOADER_HPP
