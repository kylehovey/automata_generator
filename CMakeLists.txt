cmake_minimum_required(VERSION 3.6)

project(Project)

add_definitions("-Wall" "-g" "-std=c++1z" "-O3" "-Wall" "-Wextra" "-Werror")

include_directories(${PROJECT_SOURCE_DIR})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(run ${SRC_FILES})
