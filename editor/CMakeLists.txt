set(EDITOR_SOURCES
        src/MazeGenerator/MazeGenerator.cpp
        src/MazeGenerator/MazeGenerator.hpp
        src/Maze/Maze.hpp
        src/Maze/Maze.cpp
        src/Maze/CellState.hpp
        src/GameEditor/GameEditor.cpp
        src/GameEditor/GameEditor.hpp
)

add_library(editor_lib ${EDITOR_SOURCES})

target_include_directories(editor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(editor_lib PUBLIC nlohmann_json::nlohmann_json boost::boost)

add_executable(editor_exec src/main.cpp)
target_link_libraries(editor_exec PRIVATE editor_lib)
