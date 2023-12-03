include_directories(include)

add_library(ConfigParser
            src/ConfigParser.cpp src/ConfigParserExceptions.cpp src/ConvertersConfigParsers.cpp)
            
target_include_directories(ConfigParser PUBLIC include)

target_link_libraries(ConfigParser Converter )