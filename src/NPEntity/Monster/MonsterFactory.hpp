/**
 * @file MonsterFactory.hpp
 * @ingroup Game
 * @brief Factory class for creating Monster instances from parameters or JSON.
 */

#ifndef MONSTERFACTORY_HPP
#define MONSTERFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class NPEntity;
struct Stats;
class Monster;

/**
 * @brief A factory class for creating Monster instances.
 *
 * Provides utilities to create monsters manually or from JSON data.
 */
class MonsterFactory {
 public:
  /**
   * @brief Creates a new Monster with calculated defense multiplier.
   *
   * The defense multiplier is scaled based on the monster's level.
   *
   * @param name The name of the monster.
   * @param level The monster's level.
   * @param stats The monster's stats (strength, mana, max health).
   * @return Pointer to a new Monster object.
   */
  static Monster* createMonster(const std::string& name, unsigned level,
                                const Stats& stats);

  /**
   * @brief Creates a Monster from a JSON object.
   *
   * Parses the monster's name, level, stats, and defense scaling from JSON
   * data.
   *
   * @param monsterJson JSON object containing monster attributes.
   * @return Pointer to a new Monster object cast as an NPEntity.
   * @throws std::runtime_error if a an improper value is read from the JSON
   */
  static NPEntity* createMonsterFromJson(const nlohmann::json& monsterJson);

 private:
  /**
   * @brief Base resistance multiplier applied to monster defense.
   */
  static constexpr double scalesDefenceMult = 0.15;

  /**
   * @brief Resistance multiplier bonus per level above 1.
   */
  static constexpr double scalesDefLvlUpBonus = 0.05;
};

#endif  // MONSTERFACTORY_HPP
