#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>

#include "cmds.h"
#include "memory/mem.h"
#include "shell/shell.h"
#include "capstone/caprock.h"

static void print_hex(uint8_t *buf, char *addr, size_t size);

int examine_cmd(ctx_t *ctx, char *arg)
{
    /* Get token and parse them */
    char **args = shell_tokenize(arg, 3);
    if (!args) {
        return -1;
    }

    /* Format args */
    char format = *args[0];
    size_t size = atoi(args[1]);
    char *addr_str = args[2];
    void *addr;
    sscanf(addr_str, "%p", (void **)&addr);
    free(args);

    uint8_t buf[size];
    read_mem(ctx->pid, addr, buf, size);

    switch (format) {
    case 'i':
        if (print_disasm((uint64_t)addr, buf, size) < 0) {
            return -1;
        }
        break;
    case 'x':
        print_hex(buf, addr_str, size);
        break;
    default :
        printf("Format specified is not valid\n");
        return -1;
    }

    return 0;
}
shell_cmd(examine, examine_cmd);

static void print_hex(uint8_t *buf, char *addr, size_t size)
{
    printf("%s = 0x", addr);
    for (size_t i = 0; i < size; ++i) {
        printf("%X", buf[i]);
    }
    printf("\n");
}
