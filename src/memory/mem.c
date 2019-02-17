#define _GNU_SOURCE
#include <sys/uio.h>

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
