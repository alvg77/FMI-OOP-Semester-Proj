#ifndef CELL_HPP
#define CELL_HPP

class NPEntity;
class Hero;

class Cell {
 public:
  Cell(const NPEntity* entity = nullptr);
  Cell(const Cell& other);
  Cell& operator=(const Cell& other);
  ~Cell();

  void addEntity(NPEntity* entity);
  void removeEntity();

  bool step(Hero& hero);
  void interact(Hero& hero);

  char getSymbol() const;

 private:
  NPEntity* entity;

  static constexpr char emptySymbol = '.';
};

#endif  // CELL_HPP
