add_executable(game_tests game/test_main.cpp
        game/HeroTest.cpp)
target_link_libraries(game_tests PRIVATE game_lib doctest::doctest)

add_executable(editor_tests editor/test_main.cpp
        editor/MazeTest.cpp
        editor/MazeGeneratorTest.cpp)
target_link_libraries(editor_tests PRIVATE editor_lib doctest::doctest)
