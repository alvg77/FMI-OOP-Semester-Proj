#include "HeroRace.hpp"

std::string_view getHeroRaceName(HeroRace heroRace) {
  switch (heroRace) {
    case HeroRace::HUMAN:
      return "human";
    case HeroRace::ELF:
      return "elf";
    default:
      return "[unknown race]";
  }
}

HeroRace getHeroRace(const std::string& heroRaceStr) {
  if (heroRaceStr == "human") {
    return HeroRace::HUMAN;
  }
  if (heroRaceStr == "elf") {
    return HeroRace::ELF;
  }
  throw std::invalid_argument("No such hero race: " + heroRaceStr);
}