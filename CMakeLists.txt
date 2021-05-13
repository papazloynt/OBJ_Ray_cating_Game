cmake_minimum_required(VERSION 3.16.3)
project(RayCast)

set(CMAKE_CXX_STANDARD 14)

add_library(ray_cast STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamewindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ppm_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/textures.cpp)

target_include_directories(ray_cast PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/soft)


add_executable(images
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(images PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include)

target_link_libraries(images PUBLIC
        ray_cast)
