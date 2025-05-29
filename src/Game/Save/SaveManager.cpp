#include "SaveManager.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

#include "../../Entity/Creature/Hero/Hero.hpp"
#include "../../Map/Map.hpp"
#include "../GameContext.hpp"

enum class ItemType;

const std::string SaveManager::saveFileLoc = "../data/save/savedata.json";

void SaveManager::save(const GameContext& ctx) {
  if (ctx.map == nullptr || ctx.hero == nullptr) {
    throw std::runtime_error(
        "Map and hero should have values upon calling save game!");
  }

  using nlohmann::json;

  std::ofstream file(SaveManager::saveFileLoc);
  if (!file.is_open()) {
    throw std::invalid_argument("Cannot open file!");
  }

  json jsonWriter;
  jsonWriter["hero"] = ctx.hero->toJson();
  jsonWriter["map"] = ctx.map->toJson();

  file << jsonWriter.dump(2);

  file.close();
}

GameContext SaveManager::loadGame() {
  using nlohmann::json;

  GameContext ctx{};

  std::ifstream file(SaveManager::saveFileLoc);

  if (!file.is_open()) {
    file.close();
    throw std::runtime_error("Save file does not exist!");
  }

  json jsonData;

  file >> jsonData;

  ctx.hero = new Hero(jsonData["hero"]);
  ctx.map = new Map(jsonData["map"]);

  file.close();

  return ctx;
}


