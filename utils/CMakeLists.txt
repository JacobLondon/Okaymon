set(util_source_files
    eventloop.cpp
    eventloop.hpp
    modules.cpp
    modules.hpp
    slots.cpp
    slots.hpp
    time.cpp
    time.hpp
)

add_library(util ${util_source_files})
target_compile_options(util PRIVATE -Wall -Wextra)
