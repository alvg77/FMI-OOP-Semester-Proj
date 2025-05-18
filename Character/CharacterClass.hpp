#ifndef CHARACTERCLASS_HPP
#define CHARACTERCLASS_HPP

#include <iostream>

enum class CharacterClass
{
    FIGHTER,
    MAGE,
    ADVENTURER
};

inline std::ostream& operator<<(std::ostream& os, const CharacterClass& c)
{
    switch (c)
    {
    case CharacterClass::FIGHTER:
        os << "FIGHTER";
        break;
    case CharacterClass::MAGE:
        os << "MAGE";
        break;
    case CharacterClass::ADVENTURER:
        os << "ADVENTURER";
        break;
    default:
        os << "UNKNOWN";
    }

    return os;
}

#endif //CHARACTERCLASS_HPP
