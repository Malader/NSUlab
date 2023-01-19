include_directories(include)

add_library(matrix_field
        src/MoveMatrix.cpp
        src/ResultMatrix.cpp
        src/PlayingField.cpp)

target_include_directories(matrix_field PUBLIC include)

target_link_libraries(matrix_field strategies)