file(GLOB elflib_src
        *.h
        *.c
)

add_library(elflib STATIC ${elflib_src})
