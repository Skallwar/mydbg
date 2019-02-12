#include <stdio.h>

#include "cmds.h"

int info_mem(ctx_t *ctx, char *arg)
{
    char path[64];
    sprintf(path, "/proc/%i/maps", ctx->pid);

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
shell_cmd(info_mem, info_mem);

