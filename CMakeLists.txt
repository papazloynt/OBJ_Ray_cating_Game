cmake_minimum_required(VERSION 3.8)
project(RayCast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_library(ray_cast STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamewindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ppm_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/textures.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sprite_drawing.cpp)

target_include_directories(ray_cast PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(images
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gui.cpp)

target_include_directories(images PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(images
        ray_cast
        ${SDL2_LIBRARIES})
