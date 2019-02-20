#include <stdlib.h>
#include <stdio.h>

#include "cmds.h"
#include "shell/shell.h"
#include "breakpoint/brkp.h"

int tbreak_cmd (ctx_t *ctx, char *arg)
{
    char **args = shell_tokenize(arg, 1);
    if (!args) {
        return -1;
    }

    char *addr_str = args[0];
    uint64_t *addr;
    sscanf(addr_str, "%p", (uint64_t **)&addr);

    free(args);

    brkp_t *brkp = brkp_new(ctx, addr, true);
    int err = brkp_set(ctx, brkp);

    return err;
}
shell_cmd(tbreak, tbreak_cmd);
