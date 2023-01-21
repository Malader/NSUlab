include_directories(include)

add_library(WAV
        src/WAVReader.cpp include/WAVWriter.hpp src/WAVWriter.cpp src/WavExceptions.cpp)
            
target_include_directories(WAV PUBLIC include)