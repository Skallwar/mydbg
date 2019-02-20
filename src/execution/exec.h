#ifndef EXEC_H
#define EXEC_H

#include "dbg.h"

/* Resume tracee with signal handling, return error code */
int exec_resume(ctx_t *ctx);
/* Single step tracee with signal handling, return error code */
int exec_singlestep(ctx_t *ctx);

#endif
