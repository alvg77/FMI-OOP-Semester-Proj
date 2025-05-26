#ifndef CHARACTERCREATOR_HPP
#define CHARACTERCREATOR_HPP

#include "../../Entity/Creature/Hero/Hero.hpp"

class CharacterCreator {
 public:
  static Hero* createHero();

 private:
  static Stats getInitialStats(HeroClass clas);
  static Stats getRacialBonus(HeroRace race);
};

#endif  // CHARACTERCREATOR_HPP
