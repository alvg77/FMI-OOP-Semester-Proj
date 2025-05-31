/**
 * @file Wall.hpp
 * @ingroup Game
 * @brief Defines the Wall class representing a non-passable wall entity in the
 * game.
 */

#ifndef WALL_HPP
#define WALL_HPP

#include "../NPEntity.hpp"

/**
 * @class Wall
 * @brief Represents a non-passable wall entity in the game.
 *
 * A Wall is an NPEntity that blocks player movement and cannot be interacted
 * with in any meaningful way.
 */
class Wall final : public NPEntity {
 public:
  /**
   * @brief Called when the Hero attempts to step onto the Wall.
   * @param hero Reference to the Hero attempting to move.
   * @return Always returns false since Walls cannot be stepped on.
   */
  bool onStep(Hero& hero) override;

  /**
   * @brief Called when the Hero interacts with the Wall.
   * @param hero Reference to the Hero interacting with the Wall.
   *
   * This implementation does nothing, as Walls are non-interactive.
   */
  void onInteract(Hero& hero) override;

  /**
   * @brief Gets the symbol used to represent the Wall.
   * @return A character representing the Wall ('#').
   */
  char getSymbol() const override;

  /**
   * @brief Creates a copy of this Wall.
   * @return A pointer to a new Wall object cloned from this one.
   */
  Wall* clone() const override;

 private:
  /// Symbol used to represent the wall on the game map.
  static constexpr char wallSymbol = '#';
};

#endif  // WALL_HPP
