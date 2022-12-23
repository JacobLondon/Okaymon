set(game_source_files
    entry.cpp
    entry.hpp
    mod_battle.cpp
    mod_battle.hpp
    mod_raylib.cpp
    mod_raylib.hpp
)

add_library(game ${game_source_files})
target_compile_options(game PRIVATE -Wall -Wextra)
