/**
 * @file CharacterCreator.hpp
 * @ingroup Game
 * @brief Provides functionality for interactively creating a Hero character.
 */

#ifndef CHARACTERCREATOR_HPP
#define CHARACTERCREATOR_HPP

#include "../../Entity/Creature/Hero/Hero.hpp"

/**
 * @brief Provides functionality for interactively creating a Hero character.
 *
 * This class handles user input for selecting a name, race, and class,
 * and equips the Hero with default items.
 */
class CharacterCreator {
 public:
  /**
   * @brief Creates a new Hero based on user input.
   *
   * Prompts the user for the Hero's name, race, and class, and returns a fully
   * initialized Hero equipped with basic starting gear.
   *
   * @return A dynamically allocated Hero instance.
   */
  static Hero* createHero();
};

#endif  // CHARACTERCREATOR_HPP
