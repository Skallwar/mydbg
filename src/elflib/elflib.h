#ifndef ELFLIB_H
#define ELFLIB_H

#include <stddef.h>
#include <elf.h>

/* #include "../vect/vect.h" */

typedef struct {
    uint8_t *buf;
    size_t size;
    const char *path;
} elf_t;

/* typedef struct { */
/*     Elf64_Phdr *phdr; */
/*     vect_t *shdr_vect; */
/* } phdr_t; */

/* typedef struct { */
/*     Elf64_Shdr *shdr; */
/*     uint8_t *data; */
/* } shdr_t; */

elf_t *elf_load(const char *path);
/* void elf_save(elf32_t *elf); */

/* Acces */
Elf64_Ehdr *elf_ehdr(elf_t *elf);
Elf64_Shdr *elf_shdr(elf_t *elf, uint16_t n);
/* Elf32_Phdr *elf_phdr(elf32_t *elf, uint16_t n); */

/* Manage */
/* vect_t *shdr_list(elf32_t *elf, vect_t *shdr_vect); */
/* vect_t *phdr_gen(vect_t *shdr_vect); */
/* elf32_t *elf_build(const char *name, Elf32_Ehdr *ehdr, vect_t *phdr_vect); */

/* void elf_print(elf32_t *elf); */

#endif
