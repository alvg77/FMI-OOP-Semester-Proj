#include "HeroClass.hpp"

std::string_view getHeroClassName(const HeroClass heroClass) {
  switch (heroClass) {
    case HeroClass::WARRIOR:
      return "warrior";
    case HeroClass::MAGE:
      return "mage";
    default:
      return "[unknown class]";
  }
}

HeroClass getHeroClass(const std::string& heroClassStr) {
  if (heroClassStr == "warrior") {
    return HeroClass::WARRIOR;
  }
  if (heroClassStr == "mage") {
    return HeroClass::MAGE;
  }
  throw std::invalid_argument("No such hero class: " + heroClassStr);
}
