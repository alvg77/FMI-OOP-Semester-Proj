#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <string>

#include "CharacterClass.hpp"
#include "CharacterRace.hpp"
#include "../Monster/Monster.hpp"
#include "../Item/Item.hpp"

class Character
{
public:
    Character(std::string name, CharacterRace r, CharacterClass c);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();

    void levelUp();
    void distributePoints(unsigned str, unsigned mn, unsigned hp);

    void dealDamage(Monster& monster) const;
    void takeDamage(unsigned amount);

    void printStats(std::ostream& os = std::cout) const;

    friend void swap(Character& a, Character& b) noexcept;
private:
    std::string characterName;
    unsigned strength;
    unsigned mana;
    unsigned health;
    unsigned level;
    unsigned attrPoints;
    CharacterRace characterRace;
    CharacterClass characterClass;

    Item* armor;
    Item* weapon;
    Item* spell;

    void setInitialStats();
    void applyRacialBonus();

    static void printEquippedItem(std::ostream& os, const Item* item);
};

void swap(Character& a, Character& b) noexcept;

#endif //CHARACTER_HPP
