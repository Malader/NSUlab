include_directories(include)

add_library(game_modes
            src/Game.cpp
            src/FastGame.cpp
            src/DetailedGame.cpp
            src/TournamentGame.cpp)

target_include_directories(game_modes PUBLIC include)

target_link_libraries(game_modes PUBLIC matrix_field strategies)