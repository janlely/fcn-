cmake_minimum_required(VERSION 3.10)
project(minist-test VERSION 1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(PROJECT_TEST_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/test/)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_TEST_BINARY_DIR})
add_executable(minist-test grad_test.cpp)
#target_link_libraries(minist ${ARMADILLO} ${PROGRESSBAR} ${NCURSES})

