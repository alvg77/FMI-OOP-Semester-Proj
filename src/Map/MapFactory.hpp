#ifndef MAPFACTORY_HPP
#define MAPFACTORY_HPP

#include <nlohmann/json_fwd.hpp>

class Map;

class MapFactory {
public:
  static Map* createMap(unsigned level);
  static Map* createMapFromJson(const nlohmann::json& mapJson);
};

#endif //MAPFACTORY_HPP
