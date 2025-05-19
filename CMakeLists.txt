cmake_minimum_required(VERSION 3.22)
project(FMI_OOP_Semester_Proj)

set(CMAKE_CXX_STANDARD 14)

find_package(nlohmann_json REQUIRED)

add_executable(FMI_OOP_Semester_Proj
        main.cpp
        character/Character.cpp
        monster/Monster.cpp
        item/Item.cpp
        game_map/GameMap.cpp
)

target_link_libraries(FMI_OOP_Semester_Proj PRIVATE nlohmann_json::nlohmann_json)
