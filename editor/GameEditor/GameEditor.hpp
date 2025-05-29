#ifndef GAMEEDITOR_HPP
#define GAMEEDITOR_HPP
#include <string>

class Maze;
class GameEditor {
 public:
  static void editGameDetails();

 private:
  static void saveLevel(unsigned n, const Maze& maze, unsigned treasureN,
                 unsigned monsterN, unsigned finishRow, unsigned finishCol);

  static constexpr unsigned levelsN = 4;
  static const std::string levelMapLocation;
};

#endif  // GAMEEDITOR_HPP
