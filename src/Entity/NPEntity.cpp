#include "NPEntity.hpp"

#include <nlohmann/json.hpp>

NPEntityStatus NPEntity::getStatus() const { return status; }

nlohmann::json NPEntity::toJson() const {
  using nlohmann::json;

  return json{};
}
