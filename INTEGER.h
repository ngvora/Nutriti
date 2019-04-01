#ifndef INCLUDED_INTEGER_H
#define INCLUDED_INTEGER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct integer INTEGER;

INTEGER* newINTEGER(size_t n);

size_t getINTEGER(INTEGER* n);

bool compareINTEGER(void* n1, void* n2);

size_t hashINTEGER(void* n);

void freeINTEGER(void* n);

#endif
