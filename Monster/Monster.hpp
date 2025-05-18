//
// Created by Alek on 5/17/2025.
//

#ifndef MONSTER_HPP
#define MONSTER_HPP

class Monster {
public:
    Monster();
    Monster(unsigned level, unsigned strength, unsigned mana, unsigned health);
    void takeDamage(unsigned damage);
private:
    unsigned level;
    unsigned strength;
    unsigned mana;
    unsigned health;
    static constexpr unsigned dmgReduction = 15;
};

#endif //MONSTER_HPP
