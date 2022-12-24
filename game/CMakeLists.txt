set(game_source_files
    entry.cpp
    entry.hpp
    mod_battle.cpp
    mod_messages.cpp
    mod_moves.cpp
    mod_okaymon.cpp
    mod_raylib.cpp
    mod_world.cpp
    mod.hpp
    moves.cpp
    moves.hpp
    okaymon.cpp
    okaymon.hpp
    writer.cpp
    writer.hpp
)

add_library(game ${game_source_files})
target_compile_options(game PRIVATE -Wall -Wextra)
