#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>

#include "sym.h"
#include "elflib/elflib.h"

static Elf64_Shdr *find_symtab(elf_t *elf);
static Elf64_Shdr *elf_stringtab(elf_t *elf);
static bool sym_cmpfunc(void *key1, void *key2);
static size_t sym_hfunc(void *key);

void symbols_load(ctx_t *ctx, elf_t *elf)
{
    /* Find string tab with name of symbols */
    Elf64_Shdr *shdr_strtab = elf_stringtab(elf);
    char *strbuf = (char *)(elf->buf + shdr_strtab->sh_offset);

    /* Find symbols table */
    Elf64_Shdr *shdr_symtab = find_symtab(elf);
    if (!shdr_symtab) {
        printf("No symbol table have been loaded\n");
        return;
    }

    /* Declare struct symbol tab */
    Elf64_Sym *sym_tab = (Elf64_Sym *)(elf->buf + shdr_symtab->sh_offset);

    /* Create a htab to store symbols */
    ctx->symtab = htab_new(sym_hfunc, sym_cmpfunc);

    /* Find all globals symbols */
    size_t nb_sym = shdr_symtab->sh_size / sizeof(*sym_tab);
    for (size_t i = 0; i < nb_sym; ++i) {
        Elf64_Sym *sym = sym_tab + i;
        if (sym->st_info == ELF64_ST_INFO(STB_GLOBAL, STT_FUNC) &&
            sym->st_name) {
            void *name = strbuf + sym->st_name;
            void *ptr = (uint64_t *)sym->st_value;

            htab_add(ctx->symtab, name, ptr);
        }
    }

    printf("%lu symbols has been loaded\n", ctx->symtab->nb_elm);
}

static Elf64_Shdr *find_symtab(elf_t *elf)
{
    Elf64_Ehdr *ehdr = elf_ehdr(elf);

    for (uint16_t i = 0; i < ehdr->e_shnum; ++i) {
        Elf64_Shdr *shdr = elf_shdr(elf, i);
        if (shdr->sh_type == SHT_SYMTAB) {
            return shdr;
        }
    }

    return NULL;
}

static Elf64_Shdr *elf_stringtab(elf_t *elf)
{
    Elf64_Ehdr *ehdr = elf_ehdr(elf);
    Elf64_Shdr *shdr_shstrtab = elf_shdr(elf, ehdr->e_shstrndx);
    char *shstrtab = (char *)(elf->buf + shdr_shstrtab->sh_offset);

    for (uint16_t i = 0; i < ehdr->e_shnum; ++i) {
        Elf64_Shdr *shdr = elf_shdr(elf, i);
        if (shdr->sh_type == SHT_STRTAB &&
            !strcmp(".strtab", (char *)(shstrtab + shdr->sh_name))) {
            return shdr;
        }
    }

    return NULL;
}

static size_t sym_hfunc(void *key)
{
    char *str = (char *)key;

    size_t hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

static bool sym_cmpfunc(void *key1, void *key2)
{
    char *str1 = (char *)key1;
    char *str2 = (char *)key2;

    return !strcmp(str1, str2);
}
