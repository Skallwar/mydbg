#include <sys/ptrace.h>
#include <sys/types.h>
#include <stddef.h>

#include "regs.h"

inline void regs_get(pid_t pid, struct user_regs_struct *regs)
{
    ptrace(PTRACE_GETREGS, pid, NULL, regs);
}

inline void regs_set(pid_t pid, struct user_regs_struct *regs)
{
    ptrace(PTRACE_SETREGS, pid, NULL, regs);
}
