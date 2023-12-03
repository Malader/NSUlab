cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME lab3-SoundProcessor)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} src/main.cpp lib/SoundProcessor/include/SoundProcessorExceptions.hpp lib/SoundProcessor/src/SoundProcessorExceptions.cpp)

add_subdirectory(lib/ConfigParser)
add_subdirectory(lib/Converter)
add_subdirectory(lib/SoundProcessor)
add_subdirectory(lib/WAV)

target_link_libraries(${PROJECT_NAME} WAV SoundProcessor)