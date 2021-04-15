cmake_minimum_required(VERSION 3.17)
project(OBJgame)

set(CMAKE_CXX_STANDARD 14)

add_executable(OBJgame ../d/Raycast.cpp Map.cpp Point2D.cpp Renderer.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(OBJgame sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
endif()