#ifndef LOADEDLEVEL_HPP
#define LOADEDLEVEL_HPP

struct LoadedLevel {
  unsigned rows{};
  unsigned cols{};
  unsigned monsterN{};
  unsigned treasureN{};
  std::vector<std::vector<Cell*>> grid;
  std::vector<std::pair<unsigned, unsigned>> freeSpaces;
  std::vector<Item*> items{};
  std::vector<Monster*> monsters{};
};

#endif //LOADEDLEVEL_HPP
