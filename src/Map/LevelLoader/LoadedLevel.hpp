#ifndef LOADEDLEVEL_HPP
#define LOADEDLEVEL_HPP

struct LoadedLevel {
  unsigned rows{}, cols{};
  unsigned playerRow{}, playerCol{};
  unsigned finishRow{}, finishCol{};
  std::vector<std::vector<Cell*>> grid;
};

#endif  // LOADEDLEVEL_HPP
