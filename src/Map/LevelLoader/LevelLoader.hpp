#ifndef LEVELLOADER_HPP
#define LEVELLOADER_HPP

#include <nlohmann/json.hpp>
#include <random>
#include <vector>

class NPEntity;
class Cell;
class Item;
class Monster;
struct Stats;
class Map;

using nlohmann::json;

class LevelLoader {
 public:
  static Map* load(unsigned n);

 private:
  static void validateLevelJson(const json& data);
  static json readJson(const std::string& path);
  static void parseGrid(const json& jsonGrid,
                        std::vector<std::vector<Cell*>>& grid,
                        std::vector<std::pair<unsigned, unsigned>>& freeSpaces,
                        unsigned cols);
  static std::vector<NPEntity*> loadItems(unsigned count, unsigned n);
  static std::vector<NPEntity*> loadMonsters(unsigned count, unsigned n);
  static void placeEntitiesAtRandomAndClear(
      std::vector<NPEntity*>& entities,
      std::vector<std::pair<unsigned, unsigned>>& freeCells,
      const std::vector<std::vector<Cell*>>& grid);

  static std::mt19937 rng;
  static const std::string levelFileLocation;
  static const std::string monstersFileLocation;
  static const std::string itemsFileLocation;
};

#endif  // LEVELLOADER_HPP
