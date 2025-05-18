#include "Character.hpp"

Character::Character(std::string name, const CharacterRace r, const CharacterClass c)
        : characterName(std::move(name)),
          strength(0),
          mana(0),
          health(50),
          level(1),
          attrPoints(0),
          characterRace(r),
          characterClass(c),
          armor(nullptr),
          weapon(new Item{"Iron Sword", 20}),
          spell(new Item{"Firebolt", 20})
{
    setInitialStats();
    applyRacialBonus();
}

Character::Character(const Character& other)
        : characterName(other.characterName),
          strength(other.strength),
          mana(other.mana),
          health(other.health),
          level(other.level),
          attrPoints(other.attrPoints),
          characterRace(other.characterRace),
          characterClass(other.characterClass),
          armor(nullptr),
          weapon(nullptr),
          spell(nullptr)
{
    if (other.armor != nullptr)
    {
        armor = new Item(*other.armor);
    }

    if (other.weapon != nullptr)
    {
        weapon = new Item(*other.weapon);
    }

    if (other.spell != nullptr)
    {
        spell = new Item(*other.spell);
    }
}

Character& Character::operator=(const Character& other)
{
    if (this != &other)
    {
        Character temp(other);
        swap(temp, *this);
    }

    return *this;
}

Character::~Character()
{
    delete armor;
    delete spell;
    delete weapon;
}

void Character::levelUp()
{
    ++level;
    attrPoints = 30;
}

void Character::distributePoints(const unsigned str, const unsigned mn, const unsigned hp)
{
    if (str + mn + hp > strength)
    {
        std::cout << "Not enough points to distribute" << std::endl;
        return;
    }
    strength += str;
    mana += mn;
    health += hp;

    attrPoints -= str + mn + hp;
}

void Character::dealDamage(Monster& monster) const
{

}

void Character::takeDamage(unsigned amount)
{
    unsigned damage = amount;
    if (armor != nullptr)
    {
        damage -= amount * armor->bonus;
    }

    health -= damage;
}

void Character::printStats(std::ostream& os) const
{
    os << "Character: " << characterName << std::endl;
    os << "Race: " << characterRace << std::endl;
    os << "Class: " << characterClass << std::endl;
    os << "Level: " << level << std::endl;
    os << "AttrPoints: " << attrPoints << std::endl;
    os << "Health: " << health << std::endl;
    os << "Strength: " << strength << std::endl;
    os << "Mana: " << mana << std::endl;

    os << "Armor: ";
    Character::printEquippedItem(os, armor);
    os << "Weapon: ";
    Character::printEquippedItem(os, weapon);
    os << "Spell: ";
    Character::printEquippedItem(os, spell);
}

void Character::setInitialStats()
{
    switch (characterClass)
    {
    case CharacterClass::FIGHTER:
        strength = 40;
        mana = 10;
        break;
    case CharacterClass::MAGE:
        strength = 10;
        mana = 40;
        break;
    case CharacterClass::ADVENTURER:
        strength = 30;
        mana = 30;
        break;
    default:
        throw std::invalid_argument("Invalid character class!");
    }
}

void Character::applyRacialBonus()
{
    switch (characterRace)
    {
    case CharacterRace::HUMAN:
        strength += 10;
        health += 10;
        mana += 10;
        break;
    case CharacterRace::ELF:
        mana += 20;
        health += 10;
        break;
    case CharacterRace::DWARF:
        strength += 10;
        health += 20;
        break;
    default:
        throw std::invalid_argument("Invalid character race!");
    }
}

void Character::printEquippedItem(std::ostream& os, const Item* item)
{
    if (item != nullptr)
    {
        os << *item << std::endl;
    }
    else
    {
        os << "No item equipped" << std::endl;
    }
}

void swap(Character& a, Character& b) noexcept
{
    using std::swap;
    swap(a.characterName, b.characterName);
    swap(a.strength, b.strength);
    swap(a.mana, b.mana);
    swap(a.health, b.health);
    swap(a.level, b.level);
    swap(a.attrPoints, b.attrPoints);
    swap(a.characterRace, b.characterRace);
    swap(a.characterClass, b.characterClass);
    swap(a.armor, b.armor);
    swap(a.weapon, b.weapon);
    swap(a.spell, b.spell);
}


