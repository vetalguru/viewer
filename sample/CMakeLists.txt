cmake_minimum_required(VERSION 3.15)

project(sample LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${LIBVBF_DIR}/include)

target_link_libraries(${PROJECT_NAME} vbf)
