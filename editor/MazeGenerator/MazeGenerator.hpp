#ifndef MAZEGENERATOR_HPP
#define MAZEGENERATOR_HPP

class Maze;

class MazeGenerator {
 public:
  static Maze generate(unsigned rows, unsigned cols);
};

#endif  // MAZEGENERATOR_HPP
