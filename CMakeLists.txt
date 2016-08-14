cmake_minimum_required(VERSION 3.0)
project(frag-engine)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(fragengine SHARED src/fragengine.cpp)
target_link_libraries(fragengine SDL2)