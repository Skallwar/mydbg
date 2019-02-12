#include <stdio.h>

#include "cmds.h"

static int print_file(char *path);

int info_mem(ctx_t *ctx, char *arg)
{
    char path[64];
    sprintf(path, "/proc/%i/maps", ctx->pid);

    return print_file(path);
}
shell_cmd(info_mem, info_mem);

static int print_file(char *path)
{
    FILE *map = fopen(path, "r");
    if (!map) {
        return -1;
    }

    char c;
    while((c = fgetc(map)) != EOF) {
        printf("%c", c);
    }

    fclose(map);

    return 0;
}
