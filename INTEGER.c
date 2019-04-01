#include "INTEGER.h"
#include <assert.h>
#include <stdlib.h>

struct integer
{
    size_t n;
};

INTEGER* newINTEGER(size_t n)
{
    INTEGER* i = malloc(sizeof(INTEGER));
    assert(i != NULL);
    i->n = n;

    return i;
}

size_t getINTEGER(INTEGER* n)
{
    assert(n != NULL);
    return ((INTEGER*)n)->n;
}

bool compareINTEGER(void* n1, void* n2)
{
    assert(n1 != NULL && n2 != NULL);

    return ((INTEGER*)n1)->n == ((INTEGER*)n2)->n;
}

size_t hashINTEGER(void* n)
{
    assert(n != NULL);
    return ((INTEGER*)n)->n * 2654435761; // Knuth multiplicative method
}

void freeINTEGER(void* n)
{
    assert(n != NULL);
    free(n);
}
