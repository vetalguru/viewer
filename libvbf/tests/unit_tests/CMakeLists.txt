cmake_minimum_required(VERSION 3.15)

project(vbf_unit_tests)

enable_testing()

set(UNIT_TESTS_LIST ut_test.cpp)

add_executable(${PROJECT_NAME} ${UNIT_TESTS_LIST})
target_link_libraries(${PROJECT_NAME}
    gtest gtest_main vbf)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${LIBVBF_DIR}/include)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME} ${UNIT_TESTS_LIST})
