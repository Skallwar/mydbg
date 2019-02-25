#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include "elflib.h"

static inline bool elf_isvalid(elf_t *elf);

elf_t *elf_load(const char *path)
{
    assert(path);

    struct stat *statbuf = malloc(sizeof(*statbuf));
    assert(statbuf);

    if (stat(path, statbuf) == -1) {
        free(statbuf);
        return NULL;
    }

    size_t size = statbuf->st_size;

    free(statbuf);

    elf_t *elf = malloc(sizeof(*elf));
    assert(elf);

    elf->path = path;
    elf->buf = malloc(size);
    elf->size = size;
    assert(elf->buf);

    int file = open(path, O_RDONLY);
    read(file, elf->buf, elf->size);

    close(file);

    assert(elf_isvalid(elf));

    return elf;
}

static inline bool elf_isvalid(elf_t *elf)
{
    assert(elf);

    return elf->buf[EI_MAG0] == ELFMAG0 &&
           elf->buf[EI_MAG1] == ELFMAG1 &&
           elf->buf[EI_MAG2] == ELFMAG2 &&
           elf->buf[EI_MAG3] == ELFMAG3;
}

Elf64_Ehdr *elf_ehdr(elf_t *elf)
{
    assert(elf);

    return (Elf64_Ehdr *)elf->buf;
}

Elf64_Shdr *elf_shdr(elf_t *elf, uint16_t n)
{
    assert(elf);

    Elf64_Ehdr *ehdr = elf_ehdr(elf);

    assert(n < ehdr->e_shnum);

    return (Elf64_Shdr *)(elf->buf + ehdr->e_shoff + n * ehdr->e_shentsize);
}
