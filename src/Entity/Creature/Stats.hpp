#ifndef STATS_HPP
#define STATS_HPP

struct Stats {
  unsigned strength;
  unsigned mana;
  unsigned maxHealth;

  Stats operator+(const Stats& other) const;
};

#endif //STATS_HPP
