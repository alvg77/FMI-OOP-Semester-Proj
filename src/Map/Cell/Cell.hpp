/**
 * @file Cell.hpp
 * @ingroup Game
 * @brief Declares the Cell class used to represent a single tile on the game
 * map.
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <nlohmann/json_fwd.hpp>

class NPEntity;
class Hero;

/**
 * @class Cell
 * @brief Represents a single cell on the game map, which may contain an entity.
 *
 * Manages the lifecycle of an NPEntity, handles interactions with the hero,
 * and provides JSON serialization of the contained entity.
 */
class Cell {
 public:
  /**
   * @brief Constructs a Cell, optionally containing an entity.
   * @param entity Pointer to an NPEntity, or nullptr if empty.
   */
  explicit Cell(NPEntity* entity = nullptr);

  /**
   * @brief Copy constructor performs a deep copy of the contained entity.
   */
  Cell(const Cell& other);

  /**
   * @brief Copy assignment operator performs a deep copy of the contained
   * entity.
   */
  Cell& operator=(const Cell& other);

  /**
   * @brief Destructor deletes the contained entity, if any.
   */
  ~Cell();

  /**
   * @brief Replaces the current entity in the cell with a new one.
   * Deletes the old entity.
   * @param entity Pointer to the new NPEntity to add.
   */
  void addEntity(NPEntity* entity);

  /**
   * @brief Returns the JSON representation of the contained entity.
   * @return JSON object of the entity, or empty JSON if no entity present.
   */
  nlohmann::json getEntityJson() const;

  /**
   * @brief Removes and deletes the contained entity, if any.
   */
  void removeEntity();

  /**
   * @brief Handles the hero stepping onto this cell.
   * Calls the entity's onStep() method if present.
   * @param hero Reference to the hero stepping on the cell.
   * @return true if hero can proceed, false otherwise.
   */
  bool step(Hero& hero) const;

  /**
   * @brief Handles interaction between the hero and the entity in the cell.
   * If the entity becomes inactive after interaction, it is removed.
   * @param hero Reference to the hero interacting.
   */
  void interact(Hero& hero);

  /**
   * @brief Returns the character symbol representing this cell.
   * If the cell contains an entity, returns the entity's symbol;
   * otherwise returns a default empty symbol.
   * @return Character symbol for the cell.
   */
  char getSymbol() const;

 private:
  NPEntity* entity;  ///< Pointer to the entity contained in the cell, or
                     ///< nullptr if empty
  static constexpr char emptySymbol =
      '.';  ///< Symbol representing an empty cell
};

#endif  // CELL_HPP
