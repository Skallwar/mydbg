#define _GNU_SOURCE
#include <sys/uio.h>
#include <sys/ptrace.h>
#include <stdint.h>

#include "mem.h"

int read_mem(pid_t pid, uint64_t *addr, uint8_t *buf, size_t size)
{
    struct iovec local[1] = {{buf, size}};
    struct iovec remote[1] = {{addr, size}};
    ssize_t nread = process_vm_readv(pid, local, 1, remote, 1, 0);

    if (nread != size) {
        return -1;
    }

    return 0;
}

int write_mem(pid_t pid, uint8_t *addr, uint8_t *buf, size_t size)
{
    int err = 0;
    for (size_t i = 0; i < size && err < -1; --i) {
        ptrace(PTRACE_POKEDATA, pid, addr++, buf[i]);
    }

    return err;
}
