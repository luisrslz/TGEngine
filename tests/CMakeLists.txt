# fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# for windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable testing
enable_testing()

# define the test sources
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/src/algorithm.cpp
    ${CMAKE_SOURCE_DIR}/src/game.cpp
    ${CMAKE_SOURCE_DIR}/src/helpers.cpp
    ${CMAKE_SOURCE_DIR}/src/player.cpp
    ${CMAKE_SOURCE_DIR}/src/stats.cpp
)

# test executable for Game class
add_executable(test_game 
    test_game.cpp 
    ${TEST_SOURCES}
)
target_include_directories(test_game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_game GTest::gtest_main)

# test executable for Player class
add_executable(test_player 
    test_player.cpp 
    ${TEST_SOURCES}
)
target_include_directories(test_player PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_player GTest::gtest_main)

# test executable for algorithm functions
add_executable(test_algorithm 
    test_algorithm.cpp 
    ${TEST_SOURCES}
)
target_include_directories(test_algorithm PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(test_algorithm GTest::gtest_main)


# register tests with CTest
include(GoogleTest)
gtest_discover_tests(test_game)
gtest_discover_tests(test_player)
gtest_discover_tests(test_algorithm)