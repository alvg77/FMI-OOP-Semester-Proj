cmake_minimum_required(VERSION 3.22)
project(FMI_OOP_Semester_Proj)

set(CMAKE_CXX_STANDARD 14)

find_package(nlohmann_json REQUIRED)

add_executable(FMI_OOP_Semester_Proj
        main.cpp
        character/Character.hpp
        character/Character.cpp
        monster/Monster.hpp
        monster/Monster.cpp
        item/Item.hpp
        item/Item.cpp
        game_map/GameMap.hpp
        game_map/GameMap.cpp
        game_map/MoveDirection.hpp
)

target_link_libraries(FMI_OOP_Semester_Proj PRIVATE nlohmann_json::nlohmann_json)
