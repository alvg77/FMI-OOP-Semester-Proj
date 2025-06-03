cmake_minimum_required(VERSION 3.22)
project(FMI_OOP_Semester_Proj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json REQUIRED)
find_package(boost REQUIRED)
find_package(doctest REQUIRED)

add_subdirectory(game)
add_subdirectory(editor)
add_subdirectory(tests)
