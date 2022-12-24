set(game_source_files
    entry.cpp
    entry.hpp
    mod_battle.cpp
    mod_battle.hpp
    mod_moves.cpp
    mod_moves.hpp
    mod_okaymon.cpp
    mod_okaymon.hpp
    mod_raylib.cpp
    mod_raylib.hpp
    mod_world.cpp
    mod_world.hpp
    moves.cpp
    moves.hpp
    okaymon.cpp
    okaymon.hpp
)

add_library(game ${game_source_files})
target_compile_options(game PRIVATE -Wall -Wextra)
