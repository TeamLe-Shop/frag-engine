cmake_minimum_required(VERSION 3.0)
project(frag-engine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(fragengine SHARED src/fragengine.cpp src/state.cpp src/window.cpp
                              src/game.cpp)
target_link_libraries(fragengine SDL2 GL GLU)
