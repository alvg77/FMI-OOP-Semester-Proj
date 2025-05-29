#include "Cell.hpp"

#include <nlohmann/json.hpp>

#include "../../Entity/NPEntity.hpp"

Cell::Cell(const NPEntity* entity) : entity(nullptr) {
  if (entity != nullptr) {
    this->entity = entity->clone();
  }
}

Cell::Cell(const Cell& other) : entity(nullptr) {
  if (other.entity != nullptr) {
    entity = other.entity->clone();
  }
}

Cell& Cell::operator=(const Cell& other) {
  if (this != &other) {
    delete entity;
    entity = nullptr;
    if (other.entity != nullptr) {
      entity = other.entity->clone();
    }
  }

  return *this;
}

Cell::~Cell() { delete entity; }

void Cell::addEntity(const NPEntity* entity) {
  delete this->entity;
  if (entity != nullptr) {
    this->entity = entity->clone();
  }
}

nlohmann::json Cell::getEntityJson() const {
  using nlohmann::json;
  json entityJson;

  if (entity != nullptr) {
    entityJson = entity->toJson();
  }

  return entityJson;
}

void Cell::removeEntity() {
  delete this->entity;
  this->entity = nullptr;
}

bool Cell::step(Hero& hero) {
  if (entity != nullptr) {
    return entity->onStep(hero);
  }
  return true;
}

void Cell::interact(Hero& hero) {
  if (entity != nullptr) {
    entity->onInteract(hero);
    if (entity->getStatus() == NPEntityStatus::INACTIVE) {
      removeEntity();
    }
  }
}

char Cell::getSymbol() const {
  if (entity != nullptr) {
    return entity->getSymbol();
  }
  return Cell::emptySymbol;
}
