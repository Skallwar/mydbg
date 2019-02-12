#include <sys/types.h>
#include <sys/user.h>

inline void regs_get(pid_t pid, struct user_regs_struct *regs);
