cmake_minimum_required(VERSION 3.15)

project(vbf LANGUAGES CXX)

set(PUBLIC_INCLUDES include/testfile.hpp
                    include/json_parser.hpp)

set(SOURCES src/testfile.cpp
            src/json_parser.cpp)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${SOURCES} ${PUBLIC_INCLUDES})

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    include)

# Boost Json settings
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE    
    ${THIRDPARTY_DIR}/json/include)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    BOOST_JSON_STANDALONE)

add_subdirectory(tests)
