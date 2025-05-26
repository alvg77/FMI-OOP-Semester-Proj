#ifndef INTERACTIONSMANAGER_HPP
#define INTERACTIONSMANAGER_HPP

class Hero;
struct Item;

class InteractionsManager {
 public:
  static void promptHeroItemEquip(Hero& hero, const Item* item);
  static void promptHeroLevelUp(Hero& hero);
  static void promptContinue();
};

#endif
