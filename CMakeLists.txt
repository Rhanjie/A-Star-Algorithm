cmake_minimum_required(VERSION 3.12)

# Project name
project(AStarAlgorithm)
set(EXECUTABLE_NAME AStarAlgorithm)

# Directories
set(DIR_SOURCE source)
set(DIR_BIN bin)

# C++17
set(CMAKE_CXX_STANDARD 17)

# EXE
file(GLOB ALL_SOURCE_FILES "${DIR_SOURCE}/*")
add_executable(${EXECUTABLE_NAME} ${ALL_SOURCE_FILES})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/${DIR_BIN})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})
include(${CMAKE_CURRENT_LIST_DIR}/cmake-modules/Config.cmake)

# SFML
include_directories("${CMAKE_CURRENT_LIST_DIR}/${SFML_ROOT}/include")
find_package(SFML COMPONENTS system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
