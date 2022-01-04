cmake_minimum_required(VERSION 3.15)

project(sample LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${LIBVBF_DIR}/include)
target_link_libraries(${PROJECT_NAME} vbf)
