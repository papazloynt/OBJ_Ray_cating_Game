cmake_minimum_required(VERSION 3.8)
project(RayCast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Threads)

add_library(ray_cast STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamewindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/map_drawing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ppm_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/textures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite_drawing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/algorithms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/render.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/back_ground.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/draw_fon_button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/player.cpp)

target_include_directories(ray_cast PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(images
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui.cpp)

target_include_directories(images PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(images
        PUBLIC Threads::Threads
        ray_cast
        ${SDL2_LIBRARIES})
