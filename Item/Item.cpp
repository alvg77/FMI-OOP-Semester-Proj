//
// Created by Alek on 5/17/2025.
//

#include "Item.hpp"

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << item.name << ", Multiplier: " << item.bonus;
    return os;
}