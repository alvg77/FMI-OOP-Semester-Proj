#ifndef NPENTITY_HPP
#define NPENTITY_HPP

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

 protected:
  NPEntityStatus status = NPEntityStatus::ACTIVE;
};

#endif  // NPENTITY_HPP
