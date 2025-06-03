#include <doctest/doctest.h>
#include <nlohmann/json.hpp>

#include "Hero/Hero.hpp"
#include "NPEntity/Item/Item.hpp"
#include "NPEntity/Monster/Monster.hpp"

Item* createItem(const std::string& name, const double mult,
                 const ItemType type) {
  return new Item(name, mult, type);
}

Monster createTestMonster() {
  constexpr Stats monsterStats{10, 5, 50};
  return {"Goblin", 1, monsterStats, 0.0};
}

TEST_CASE("Hero deals correct weapon damage to Monster") {
  constexpr Stats stats{20, 10, 100};
  Item* weapon = createItem("Sword", 0.5, ItemType::WEAPON);

  const Hero hero("Fighter", 1, stats, 100.0, HeroRace::HUMAN,
            HeroClass::WARRIOR, weapon, nullptr, nullptr);

  Monster monster = createTestMonster();
  const double oldHealth = monster.getCurrentHealth();

  hero.dealDamage(monster, AttackType::WEAPON);

  const double newHealth = monster.getCurrentHealth();

  const double expectedDamage = stats.strength * (1.0 + weapon->getMult());

  CHECK(doctest::Approx(oldHealth - newHealth).epsilon(0.001) == expectedDamage);
}

TEST_CASE("Hero takes reduced damage with armor equipped") {
  constexpr Stats stats{15, 5, 100};
  Item* armor = createItem("Plate", 0.5, ItemType::ARMOR);

  Hero hero("Tank", 1, stats, 100.0, HeroRace::ELF, HeroClass::MAGE,
            nullptr, nullptr, armor);

  hero.takeDamage(40.0);

  CHECK(doctest::Approx(hero.toJson()["currenthealth"]) == 80.0);
}

TEST_CASE("Hero takes full damage without armor") {
  Stats stats{15, 5, 100};
  Hero hero("Bare", 1, stats, 100.0, HeroRace::HUMAN, HeroClass::WARRIOR,
            nullptr, nullptr, nullptr);

  hero.takeDamage(25.0);

  CHECK(doctest::Approx(hero.toJson()["currenthealth"]) == 75.0);
}

TEST_CASE("Hero heals if below 50% health") {
  const Stats stats{10, 10, 100};
  Hero hero("Wounded", 1, stats, 30.0, HeroRace::ELF, HeroClass::MAGE, nullptr,
            nullptr, nullptr);

  hero.heal();

  CHECK(doctest::Approx(hero.toJson()["currenthealth"]) == 50.0);
}

TEST_CASE("Hero does not heal if already above 50%") {
  const Stats stats{10, 10, 100};
  Hero hero("Healthy", 1, stats, 60.0, HeroRace::HUMAN, HeroClass::WARRIOR,
            nullptr, nullptr, nullptr);

  hero.heal();

  CHECK(doctest::Approx(hero.toJson()["currenthealth"]) == 60.0);
}

TEST_CASE("Hero level up with valid stat total") {
  Stats base{10, 10, 100};
  Stats add{10, 10, 10};

  Hero hero("Leveler", 1, base, 100.0, HeroRace::HUMAN, HeroClass::WARRIOR,
            nullptr, nullptr, nullptr);

  bool result = hero.levelUp(add);

  CHECK(result == true);
  CHECK(hero.toJson()["level"] == 2);
  CHECK(hero.toJson()["maxhealth"] == 110);
}

TEST_CASE("Hero fails level up with invalid stat total") {
  Stats base{10, 10, 100};
  Stats add{5, 5, 5};

  Hero hero("NotReady", 1, base, 100.0, HeroRace::HUMAN, HeroClass::WARRIOR,
            nullptr, nullptr, nullptr);

  bool result = hero.levelUp(add);

  CHECK(result == false);
  CHECK(hero.toJson()["level"] == 1);
  CHECK(hero.toJson()["maxhealth"] == 100);
}