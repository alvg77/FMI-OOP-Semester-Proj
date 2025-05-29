#ifndef CELL_HPP
#define CELL_HPP
#include <nlohmann/json_fwd.hpp>

class NPEntity;
class Hero;

class Cell {
 public:
  explicit Cell(const NPEntity* entity = nullptr);
  Cell(const Cell& other);
  Cell& operator=(const Cell& other);
  ~Cell();

  void addEntity(const NPEntity* entity);
  nlohmann::json getEntityJson() const;

  void removeEntity();

  bool step(Hero& hero);
  void interact(Hero& hero);

  char getSymbol() const;

 private:
  NPEntity* entity;

  static constexpr char emptySymbol = '.';
};

#endif  // CELL_HPP
