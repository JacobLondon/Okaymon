cmake_minimum_required(VERSION 3.8)

Project(OkayMin LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

link_directories("/opt/homebrew/lib")
include_directories("/opt/homebrew/include")

include_directories(PUBLIC ".")

add_subdirectory(utils)
add_subdirectory(game)

set(target_source_files
    main.cpp
)

add_executable(okay ${target_source_files})
target_compile_options(okay PRIVATE -Wall -Wextra)

target_link_libraries(okay raylib game util)

install(
    TARGETS okay
    DESTINATION usr/bin
)
