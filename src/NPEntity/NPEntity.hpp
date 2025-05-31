/**
 * @file NPEntity.hpp
 * @ingroup Game
 * @brief Abstract base class for non-player entities (NPEntity) in the game.
 */

#ifndef NPENTITY_HPP
#define NPENTITY_HPP

#include <nlohmann/json_fwd.hpp>

class Hero;

/**
 * @enum NPEntityStatus
 * @brief Represents the state of an NPEntity.
 */
enum class NPEntityStatus {
  ACTIVE,   ///< Entity is active in the game.
  INACTIVE  ///< Entity is inactive or has been removed.
};

/**
 * @class NPEntity
 * @brief Abstract interface for all non-player entities in the game world.
 *
 * This class defines the interface and common behavior for any entity
 * that is not controlled by the player (e.g., NPCs, objects, etc.).
 */
class NPEntity {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~NPEntity() = default;

  /**
   * @brief Called when the player steps on the same tile as the entity.
   * @param hero Reference to the Hero interacting with the entity.
   * @return True if an action was taken, false otherwise.
   */
  virtual bool onStep(Hero& hero) = 0;

  /**
   * @brief Called when the player explicitly interacts with the entity.
   * @param hero Reference to the Hero interacting with the entity.
   */
  virtual void onInteract(Hero& hero) = 0;

  /**
   * @brief Gets the display symbol representing the entity.
   * @return A character symbol used for visual representation.
   */
  virtual char getSymbol() const = 0;

  /**
   * @brief Gets the current status of the entity.
   * @return The current NPEntityStatus (ACTIVE or INACTIVE).
   */
  NPEntityStatus getStatus() const;

  /**
   * @brief Creates a copy of the entity.
   * @return A pointer to a new NPEntity object that is a copy of this one.
   */
  virtual NPEntity* clone() const = 0;

  /**
   * @brief Serializes the entity to a JSON object.
   * @return A JSON object representing the entity's state.
   */
  virtual nlohmann::json toJson() const;

 protected:
  /// Current status of the entity.
  NPEntityStatus status = NPEntityStatus::ACTIVE;
};

#endif  // NPENTITY_HPP
