cmake_minimum_required(VERSION 3.0)
project(frag-engine)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # OSX
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -stdlib=libc++ -g")
endif()

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${SDL2_INCLUDE_DIR}
                    ${GLEW_INCLUDE_DIR}/GL)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(${OPENGL_INCLUDE_DIR}/OpenGL)
else()
    include_directories(${OPENGL_INCLUDE_DIR}/GL)
endif()

add_library(fragengine SHARED src/fragengine.cpp src/state.cpp src/window.cpp
                              src/game.cpp src/drawing.cpp)

target_link_libraries(fragengine ${SDL2_LIBRARY} ${OPENGL_LIBRARIES}
                      ${GLEW_LIBRARY})
