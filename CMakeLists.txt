cmake_minimum_required(VERSION 3.22)
project(FMI_OOP_Semester_Proj)

set(CMAKE_CXX_STANDARD 14)

find_package(nlohmann_json REQUIRED)

add_executable(FMI_OOP_Semester_Proj
        src/main.cpp
        src/Util/Util.hpp
        src/Util/Util.cpp
        src/Entity/NPEntity.hpp
        src/Entity/Creature/Hero/Hero.hpp
        src/Entity/Creature/Monster/Monster.cpp
        src/Entity/Creature/Monster/Monster.hpp
        src/Entity/Creature/Creature.cpp
        src/Entity/Creature/Creature.hpp
        src/Entity/Item/Item.cpp
        src/Entity/Item/Item.hpp
        src/Entity/Wall/Wall.cpp
        src/Entity/Wall/Wall.hpp
        src/Entity/Creature/Stats.cpp
        src/Entity/Creature/Stats.hpp
        src/Game/GameManager.cpp
        src/Game/GameManager.hpp
        src/Game/Combat/CombatManager.cpp
        src/Game/Combat/CombatManager.hpp
        src/Map/Map.cpp
        src/Map/Map.hpp
        src/Map/Cell/Cell.cpp
        src/Map/Cell/Cell.hpp
        src/Entity/NPEntity.cpp
        src/Game/Controls/ControlsManager.cpp
        src/Game/Controls/ControlsManager.hpp
        src/Game/Interactions/InteractionsManager.cpp
        src/Game/Interactions/InteractionsManager.hpp
        src/Entity/Creature/Hero/Race/HeroRace.hpp
        src/Entity/Creature/Hero/Class/HeroClass.hpp
        src/Game/Combat/AttackType.hpp
        src/Entity/Item/ItemType.hpp
        src/Game/CharacterCreator/CharacterCreator.cpp
        src/Game/CharacterCreator/CharacterCreator.hpp
        src/Entity/Creature/Hero/Hero.cpp
        src/Map/LevelLoader/LevelLoader.cpp
        src/Map/LevelLoader/LevelLoader.hpp
        src/Map/LevelLoader/LoadedLevel.hpp
        src/Game/Save/SaveManager.cpp
        src/Game/Save/SaveManager.hpp
        src/Game/GameContext.hpp
        src/GameAction.hpp
)

target_link_libraries(FMI_OOP_Semester_Proj PRIVATE nlohmann_json::nlohmann_json)
