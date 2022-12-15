cmake_minimum_required(VERSION 3.23)

project(untitled1)

set(CMAKE_CXX_STANDARD 20)
add_library(untitled1 STATIC Bigint.cpp Bigint.h)
add_executable(Big main.cpp)
target_link_libraries(Big PUBLIC untitled1)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(TestBigInt TestBigInt.cpp)
target_link_libraries(TestBigInt PUBLIC gtest_main untitled1)