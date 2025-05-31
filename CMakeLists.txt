cmake_minimum_required(VERSION 3.22)
project(FMI_OOP_Semester_Proj)

set(CMAKE_CXX_STANDARD 14)

find_package(nlohmann_json REQUIRED)
find_package(boost REQUIRED)
find_package(Doxygen QUIET)

add_executable(FMI_OOP_Semester_Proj
        src/main.cpp
        src/Util/Util.hpp
        src/Util/Util.cpp
        src/Entity/NPEntity.hpp
        src/Entity/Creature/Hero/Hero.hpp
        src/Entity/Creature/Monster/Monster.cpp
        src/Entity/Creature/Monster/Monster.hpp
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
        src/Map/LoadedLevel.hpp
        src/Game/Save/SaveManager.cpp
        src/Game/Save/SaveManager.hpp
        src/Game/GameContext.hpp
        src/Entity/Creature/Hero/HeroFactory.cpp
        src/Entity/Creature/Hero/HeroFactory.hpp
        src/Entity/Creature/Monster/MonsterFactory.cpp
        src/Entity/Creature/Monster/MonsterFactory.hpp
        src/Entity/Item/ItemFactory.cpp
        src/Entity/Item/ItemFactory.hpp
        src/Map/MapFactory.cpp
        src/Map/MapFactory.hpp
        src/Entity/Item/ItemType.cpp
        src/Game/Combat/CoinToss.cpp
)

add_executable(FMI_OOP_Semester_Proj_Level_Editor
        editor/main.cpp
        editor/MazeGenerator/MazeGenerator.cpp
        editor/MazeGenerator/MazeGenerator.hpp
        editor/Maze/Maze.hpp
        editor/Maze/Maze.cpp
        editor/Maze/CellState.hpp
        editor/GameEditor/GameEditor.cpp
        editor/GameEditor/GameEditor.hpp
)

target_link_libraries(FMI_OOP_Semester_Proj PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(FMI_OOP_Semester_Proj_Level_Editor PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(FMI_OOP_Semester_Proj_Level_Editor PRIVATE boost::boost)

if (DOXYGEN_FOUND)
    message(STATUS "Doxygen found. You can run 'make doc_doxygen' to generate documentation.")

    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile)

    add_custom_target(doc_doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else ()
    message(STATUS "Doxygen not found. Documentation won't be generated.")
endif ()