cmake_minimum_required (VERSION 3.0)
project(MyDBG)

add_compile_options(-g -Wall -Wextra -std=c99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src/)
add_subdirectory(src)

file(GLOB mydbg_src
        src/*.c
        src/cmds/*.c
        src/signal/*.c
        src/memory/*.c
        src/symbol/*.c
        src/register/*.c
        src/capstone/*.c
        src/execution/*.c
        src/breakpoint/*.c
)

add_executable(mydbg ${mydbg_src})

target_link_libraries(mydbg
    shell
    htab
    elflib
    -lcapstone #Capstone
    -fsanitize=address -fno-omit-frame-pointer  #ASAN
)
