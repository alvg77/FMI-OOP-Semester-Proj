set(GAME_SOURCES
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

add_library(game_lib ${GAME_SOURCES})

target_include_directories(game_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(game_lib PUBLIC nlohmann_json::nlohmann_json)

add_executable(game_exec src/main.cpp)
target_link_libraries(game_exec PRIVATE game_lib)

add_custom_target(make_data_dirs ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/data/save
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/data/score
        COMMENT "Creating save and score directories in the source folder"
)
