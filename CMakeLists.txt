cmake_minimum_required(VERSION 3.10)
project(minist VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(/usr/local/include/progressbar)
find_library(ARMADILLO armadillo)
message("libarmadillo libs: ${ARMADILLO}")

find_library(PROGRESSBAR progressbar)
message("libprogressbar libs: ${PROGRESSBAR}")

find_library(NCURSES ncurses)
message("libncurses libs: ${NCURSES}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0 -fno-inline-small-functions -fno-inline-functions")
message("cxx debug flag: ${CMAKE_CXX_FLAGS_DEBUG}")


#add_library(networkd ${SRC_LIST})
#target_link_libraries(networkd ${ARMADILLO})
add_executable(minist minist.cpp ${SRC_LIST})
add_executable(minist-test grad_test.cpp ${SRC_LIST})
target_link_libraries(minist ${ARMADILLO})
target_link_libraries(minist-test ${ARMADILLO})

#add_subdirectory(test)
#enable_testing()
#add_test(minist-test ${CMAKE_SOURCE_DIR}/build/test/minist-test)
#target_link_libraries(minist ${ARMADILLO} ${PROGRESSBAR} ${NCURSES})

