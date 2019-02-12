cmake_minimum_required (VERSION 3.0)
project(MyDBG)

add_compile_options(-g -Wall -Wextra)

add_subdirectory(src)

file(GLOB mydbg_src
        src/*.c
        src/cmds/*.c
        src/regs/*.c
        src/sig/*.c
        src/mem/*.c
)

add_executable(mydbg ${mydbg_src})

target_link_libraries(mydbg
    shell
    -lcapstone #Capstone
    -fsanitize=address -fno-omit-frame-pointer  #ASAN
)
