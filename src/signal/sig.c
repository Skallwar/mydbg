#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#include "sig.h"

int sig_catch(pid_t pid)
{
    int wstatus;
    waitpid(pid, &wstatus, 0);

    return wstatus;
}

int sig_handler(int sig)
{
    if (WIFEXITED(sig)) {
        printf("Debugged program exited normally\n");
        _Exit(0);
        return 0;
    }

    if (WIFSTOPPED(sig)) {
        sig = WSTOPSIG(sig);

        switch (sig) {
            default :
                return -1;
        }
    }

    printf("A signal has been caught but no action has been implemented\n");
    return -1;
}
