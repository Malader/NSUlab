include_directories(include)

add_library(Converter
        src/MuteConverter.cpp
        src/ConverterCreator.cpp
        src/MixConverter.cpp 
        src/ConverterExceptions.cpp
        src/DoubleMixConverter.cpp)
            
target_include_directories(Converter PUBLIC include)

target_link_libraries(Converter WAV)