#include <stdlib.h>
#include <stdio.h>

#include "cmds.h"
#include "shell/shell.h"
#include "htab/htab.h"
#include "breakpoint/brkp.h"

int breakf_cmd (ctx_t *ctx, char *arg)
{
    if (!ctx->symtab) {
        printf("Impossible to use breakf because no symbol has been loaded\n");
        return -1;
    }
    char **args = shell_tokenize(arg, 1);
    if (!args) {
        return -1;
    }

    char *sym_name = args[0];
    uint64_t *addr = htab_find(ctx->symtab, sym_name);

    if (!addr) {
        printf("Symbol not found\n");
        return -1;
    }

    free(args);

    brkp_t *brkp = brkp_new(ctx, addr, false);
    int err = brkp_set(ctx, brkp);

    return err;
}
shell_cmd(breakf, breakf_cmd);
