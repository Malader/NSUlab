cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME lab2-Prisoners_Dilemma)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(lib/game)
add_subdirectory(lib/strategies)
add_subdirectory(lib/matrix-field)
add_subdirectory(lib/game-modes)

target_link_libraries(${PROJECT_NAME} game_engine)