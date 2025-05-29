#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

class Hero;
class Map;

struct GameContext {
  Hero* hero;
  Map* map;
};

#endif //GAMECONTEXT_HPP
