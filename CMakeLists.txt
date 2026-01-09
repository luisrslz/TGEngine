cmake_minimum_required(VERSION 3.15)
project("TGEngine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type defaults
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(SOURCES
    src/main.cpp
    src/algorithm.cpp
    src/game.cpp
    src/helpers.cpp
    src/player.cpp
    src/stats.cpp
    src/play.cpp
)
# executable
add_executable(TGEngine ${SOURCES})

# include
target_include_directories(TGEngine PRIVATE include)

# executable location
set_target_properties(TGEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
)

# ========== Testing ==========
option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
# ==================================
