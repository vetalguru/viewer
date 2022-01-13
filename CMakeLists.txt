cmake_minimum_required(VERSION 3.15)

project(viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)
set(LIBVBF_DIR     ${CMAKE_SOURCE_DIR}/libvbf)
set(SAMPLE_DIR     ${CMAKE_SOURCE_DIR}/sample)

add_subdirectory(${LIBVBF_DIR})
add_subdirectory(${SAMPLE_DIR})
