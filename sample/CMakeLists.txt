cmake_minimum_required(VERSION 3.15)

project(sample LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${LIBVBF_DIR}/include)

# TODO: This should be removed from sample
# Boost Json settings
include_directories(${THIRDPARTY_DIR}/json/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE
                           BOOST_JSON_STANDALONE)

target_link_libraries(${PROJECT_NAME} vbf)
