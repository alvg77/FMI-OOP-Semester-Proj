#ifndef INTERACTIONSMANAGER_HPP
#define INTERACTIONSMANAGER_HPP

class Hero;
struct Item;

class InteractionsManager {
 public:
  static void promptHeroItemEquip(Hero& hero, Item* item);
  static void promptHeroLevelUp(Hero& hero);
};

#endif
