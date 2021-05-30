cmake_minimum_required(VERSION 3.8)
project(RayCast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall  ")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(ray_cast STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamewindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ppm_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/textures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite.cpp)

target_include_directories(ray_cast PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/soft)


add_executable(images
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui.cpp)

target_include_directories(images PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include)

target_link_libraries(images
        ray_cast
        ${SDL2_LIBRARIES})
