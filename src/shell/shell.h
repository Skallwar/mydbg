#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

void shell_start(const char *name, void *ctx);
void shell_end(void);

char **shell_tokenize(char *buf, size_t size);

#endif
