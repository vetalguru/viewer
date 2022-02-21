cmake_minimum_required(VERSION 3.15)

project(sample LANGUAGES CXX)

set(HEADERS ${SAMPLE_DIR}/inc/application.hpp)

set(SOURCES ${SAMPLE_DIR}/src/main.cpp
            ${SAMPLE_DIR}/src/application.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${SAMPLE_DIR}/inc)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${LIBVBF_DIR}/include)

# TODO: This should be removed from sample
# Boost Json settings
include_directories(${THIRDPARTY_DIR}/json/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE
                           BOOST_JSON_STANDALONE)

target_link_libraries(${PROJECT_NAME} vbf)
