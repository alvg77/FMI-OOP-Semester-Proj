#ifndef ITEM_HPP
#define ITEM_HPP

#include <ostream>

struct Item {
    std::string name;
    unsigned bonus;
};

std::ostream& operator<<(std::ostream& os, const Item& item);

#endif //ITEM_HPP
