#ifndef EXEC_H
#define EXEC_H

#include "dbg.h"

/* Resume tracee with signal handling, return error code */
int resume(ctx_t *ctx);
/* Single step tracee with signal handling, return error code */
int singlestep(ctx_t *ctx);

#endif
