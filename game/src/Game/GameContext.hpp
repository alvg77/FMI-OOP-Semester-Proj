/**
 * @file GameContext.hpp
 * @ingroup Game
 * @brief Declares the GameContext struct, which stores the game's current
 * state.
 */

#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

class Hero;
class Map;

/**
 * @struct GameContext
 * @brief Holds pointers to the current game state objects.
 *
 * Contains the main hero and map instances used throughout the game.
 */
struct GameContext {
  Hero* hero;  ///< Pointer to the hero object
  Map* map;    ///< Pointer to the map object
};

#endif  // GAMECONTEXT_HPP
