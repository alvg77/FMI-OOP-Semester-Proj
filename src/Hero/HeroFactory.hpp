/**
 * @file HeroFactory.hpp
 * @ingroup Game
 * @brief Factory class for creating Hero instances either from parameters or
 * JSON.
 */

#ifndef HEROFACTORY_HPP
#define HEROFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

#include "Class/HeroClass.hpp"
#include "Race/HeroRace.hpp"

class Item;
enum class HeroRace;
struct Stats;
class Hero;

/**
 * @brief Factory class for creating Hero instances.
 *
 * Provides static methods to instantiate Hero objects either from scratch or
 * using a serialized JSON object.
 */
class HeroFactory {
 public:
  /**
   * @brief Creates a new Hero with specified attributes and equipment.
   *
   * @param name Name of the hero.
   * @param level Starting level of the hero.
   * @param heroRace Race of the hero (e.g., Human, Elf).
   * @param heroClass Class of the hero (e.g., Warrior, Mage).
   * @param weapon Pointer to the weapon to equip.
   * @param spell Pointer to the spell to equip.
   * @param armor Pointer to the armor to equip.
   * @return Pointer to the created Hero instance.
   */
  static Hero* createHero(const std::string& name, unsigned level,
                          HeroRace heroRace, HeroClass heroClass, Item* weapon,
                          Item* spell, Item* armor);

  /**
   * @brief Creates a new Hero from a JSON object.
   *
   * The JSON must contain valid keys for name, level, stats, race, class,
   * current health, and items.
   *
   * @param heroJson The JSON object containing hero data.
   * @return Pointer to the created Hero instance.
   * @throws std::invalid_argument if any required fields are missing,
   *         or if current health is non-positive.
   * @throws nlohmann::json::exception if JSON keys have wrong types.
   */
  static Hero* createHeroFromJson(const nlohmann::json& heroJson);

 private:
  /**
   * @brief Returns the initial stats for a given hero class.
   *
   * @param hClass The hero class.
   * @return Stats structure with base values for the class.
   * @throws std::invalid_argument if the hero class is invalid.
   */
  static Stats getInitialStats(HeroClass hClass);

  /**
   * @brief Returns the racial bonus stats for a given race.
   *
   * @param race The hero race.
   * @return Stats structure with bonus values for the race.
   * @throws std::invalid_argument if the hero class is invalid.
   */
  static Stats getRacialBonus(HeroRace race);
};

#endif  // HEROFACTORY_HPP
