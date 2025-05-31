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
        src/NPEntity/NPEntity.hpp
        src/Hero/Hero.hpp
        src/NPEntity/Monster/Monster.cpp
        src/NPEntity/Monster/Monster.hpp
        src/NPEntity/Item/Item.cpp
        src/NPEntity/Item/Item.hpp
        src/NPEntity/Wall/Wall.cpp
        src/NPEntity/Wall/Wall.hpp
        src/Stats/Stats.cpp
        src/Stats/Stats.hpp
        src/Game/GameManager.cpp
        src/Game/GameManager.hpp
        src/Game/Combat/CombatManager.cpp
        src/Game/Combat/CombatManager.hpp
        src/Map/Map.cpp
        src/Map/Map.hpp
        src/Map/Cell/Cell.cpp
        src/Map/Cell/Cell.hpp
        src/NPEntity/NPEntity.cpp
        src/Game/Controls/ControlsManager.cpp
        src/Game/Controls/ControlsManager.hpp
        src/Game/Interactions/InteractionsManager.cpp
        src/Game/Interactions/InteractionsManager.hpp
        src/Hero/Race/HeroRace.hpp
        src/Hero/Class/HeroClass.hpp
        src/Game/Combat/AttackType.hpp
        src/NPEntity/Item/ItemType.hpp
        src/Game/CharacterCreator/CharacterCreator.cpp
        src/Game/CharacterCreator/CharacterCreator.hpp
        src/Hero/Hero.cpp
        src/Map/LevelLoader/LevelLoader.cpp
        src/Map/LevelLoader/LevelLoader.hpp
        src/Map/LoadedLevel.hpp
        src/Game/Save/SaveManager.cpp
        src/Game/Save/SaveManager.hpp
        src/Game/GameContext.hpp
        src/Hero/HeroFactory.cpp
        src/Hero/HeroFactory.hpp
        src/NPEntity/Monster/MonsterFactory.cpp
        src/NPEntity/Monster/MonsterFactory.hpp
        src/NPEntity/Item/ItemFactory.cpp
        src/NPEntity/Item/ItemFactory.hpp
        src/Map/MapFactory.cpp
        src/Map/MapFactory.hpp
        src/NPEntity/Item/ItemType.cpp
        src/Game/Combat/CoinToss.cpp
        src/Hero/Class/HeroClass.cpp
        src/Hero/Race/HeroRace.cpp
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