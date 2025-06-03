#include "GameEditor.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Maze/Maze.hpp"
#include "../MazeGenerator/MazeGenerator.hpp"

const std::string GameEditor::levelMapLocation = "../../data/levels/";

void GameEditor::editGameDetails() {
  std::cout << "-----------------" << std::endl;
  std::cout << "=== GAME EDITOR ===" << std::endl;
  std::cout << "-----------------" << std::endl;

  unsigned levelN;
  bool valid;

  do {
    valid = true;
    std::cout << "Select level number to generate (1-" << levelsN << "): ";
    std::cin >> levelN;

    if (levelN < 1 || levelN > levelsN) {
      valid = false;
      std::cout << "Invalid level number!" << std::endl;
    }
  } while (!valid);

  unsigned rows, cols;
  do {
    valid = true;
    std::cout << "Enter rows and columns (odd numbers, >=11): ";
    std::cin >> rows >> cols;

    if (rows < 11 || cols < 11 || rows % 2 == 0 || cols % 2 == 0) {
      valid = false;
      std::cout << "Rows and columns must be odd and >= 11!" << std::endl;
    }
  } while (!valid);

  unsigned monsterN, treasureN;
  do {
    valid = true;
    std::cout << "Enter number of monsters and treasures (each < 10): ";
    std::cin >> monsterN >> treasureN;

    if (monsterN >= 10 || treasureN >= 10) {
      valid = false;
      std::cout << "Number must be less than 10!" << std::endl;
    }
  } while (!valid);

  const Maze maze = MazeGenerator::generate(rows, cols);
  std::cout << "\nGenerated Maze:" << std::endl;
  maze.display();

  unsigned finishRow, finishCol;
  do {
    valid = true;
    std::cout << "Enter finish cell coordinates (row col): ";
    std::cin >> finishRow >> finishCol;

    if (!maze.isWithinBounds(finishRow, finishCol) || maze.isWall(finishRow, finishCol)) {
      valid = false;
      std::cout << "Invalid finish cell! Must be a walkable path within bounds." << std::endl;
    }
  } while (!valid);

  try {
    saveLevel(levelN, maze, treasureN, monsterN, finishRow, finishCol);
    std::cout << "Level saved successfully!" << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error saving level: \n" << e.what() << std::endl;
  }
}

void GameEditor::saveLevel(const unsigned n, const Maze& maze,
                           const unsigned treasureN, const unsigned monsterN,
                           const unsigned finishRow, const unsigned finishCol) {
  using nlohmann::json;
  json jsonData = maze.toJson();
  jsonData["treasureN"] = treasureN;
  jsonData["monsterN"] = monsterN;
  jsonData["finishRow"] = finishRow;
  jsonData["finishCol"] = finishCol;

  std::ofstream file(GameEditor::levelMapLocation + "level" +
                     std::to_string(n) + ".json");

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open/create level file!");
  }

  file << jsonData.dump(2);
  file.close();
}
