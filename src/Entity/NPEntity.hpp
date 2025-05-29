#ifndef NPENTITY_HPP
#define NPENTITY_HPP

#include <nlohmann/json_fwd.hpp>

class Hero;

enum class NPEntityStatus { ACTIVE, INACTIVE };

class NPEntity {
 public:
  virtual ~NPEntity() = default;
  virtual bool onStep(Hero& hero) = 0;
  virtual void onInteract(Hero& hero) = 0;
  virtual char getSymbol() const = 0;
  NPEntityStatus getStatus() const;
  virtual NPEntity* clone() const = 0;
  virtual nlohmann::json toJson() const;

 protected:
  NPEntityStatus status = NPEntityStatus::ACTIVE;
};

#endif  // NPENTITY_HPP
