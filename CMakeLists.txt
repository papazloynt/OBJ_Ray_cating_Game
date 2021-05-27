cmake_minimum_required(VERSION 3.8)
project(RayCast)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -ggdb3 ")


#[[
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/soft/third_party/SFML")
]]

add_library(ray_cast STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

target_include_directories(ray_cast PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}/soft)


add_executable(images
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(images PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}/include)

target_link_libraries(images PUBLIC
        ray_cast)
