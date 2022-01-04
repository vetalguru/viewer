cmake_minimum_required(VERSION 3.15)

project(vbf LANGUAGES CXX)

set(INCLUDES include/testfile.hpp)

set(SOURCES src/testfile.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(tests)
