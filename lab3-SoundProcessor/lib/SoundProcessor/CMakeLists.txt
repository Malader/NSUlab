include_directories(include)

add_library(SoundProcessor
        src/SoundProcessor.cpp
        src/SoundProcessorExceptions.cpp)
            
target_include_directories(SoundProcessor PUBLIC include)

target_link_libraries(SoundProcessor WAV ConfigParser)