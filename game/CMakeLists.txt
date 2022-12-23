set(game_source_files
    battle.cpp
    battle.hpp
    entry.cpp
    entry.hpp
)

add_library(game ${game_source_files})
target_compile_options(game PRIVATE -Wall -Wextra)
