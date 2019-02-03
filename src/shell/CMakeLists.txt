file(GLOB shell_src
        *.h
        *.c
)

add_library(shell STATIC ${shell_src})

target_link_libraries(shell
    -lreadline
)
