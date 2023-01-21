include_directories(include)

add_library(strategies
        src/AlwaysBetrayerStrategy.cpp
        src/AlternatingStrategy.cpp
        src/RandomStrategy.cpp
        src/SmartStrategy.cpp
        src/StrategyFactory.cpp
        src/PersonStrategy.cpp
        src/MetaStrategy.cpp
        )

target_include_directories(strategies PUBLIC include)

target_link_libraries(strategies matrix_field)