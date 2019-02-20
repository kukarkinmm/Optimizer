cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

project(optimizer)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

file(GLOB OPTIMIZER_SOURCE "src/*.cpp")
file(GLOB OPTIMIZER_HEADERS "includes/*.h")
add_library(optimizer ${OPTIMIZER_SOURCE} ${OPTIMIZER_HEADERS})
target_include_directories(optimizer PUBLIC headers)
target_link_libraries(optimizer)

add_executable(optimizer_test main.cpp)
target_link_libraries(optimizer_test optimizer)
