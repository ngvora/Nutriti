#include "UNORDEREDSET.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
} INTEGER;

INTEGER* newINTEGER(int value)
{
    INTEGER* i = malloc(sizeof(INTEGER));
    assert(i != NULL);
    i->value = value;
    return i;
}

bool compareINTEGER(void* i1, void* i2)
{
    assert(i1 != NULL);
    assert(i2 != NULL);

    return ((INTEGER*)i1)->value == ((INTEGER*)i2)->value;
}

void freeINTEGER(void* i)
{
    assert(i != NULL);
    free(i);
}

size_t hashINTEGER(void* i)
{
    assert(i != NULL);
    return (size_t)((INTEGER*)i)->value;
}

void* cloneINTEGER(void* i)
{
    assert(i != NULL);
    return newINTEGER(((INTEGER*)i)->value);
}

void printINTEGER(void* i, void* unused)
{
    (void)unused;

    if (i == NULL)
        printf("_ ");
    else
        printf("%d ", ((INTEGER*)i)->value);
}

int main(void)
{
    const size_t length = 50;

    INTEGER** integers = malloc(sizeof(INTEGER*) * length);

    for (size_t i = 0; i < length; i++)
    {
        integers[i] = newINTEGER(rand() % 50);
    }

    UNORDEREDSET* table = newUNORDEREDSET(hashINTEGER, compareINTEGER, freeINTEGER);
    reserveUNORDEREDSET(table, 50);

    for (size_t i = 0; i < length; i++)
    {
        insertUNORDEREDSET(table, cloneINTEGER(integers[i]));
        printf("Inserting %d\n", integers[i]->value);
        foreachUNORDEREDSET(table, printINTEGER, NULL);
        printf("\n");
    }

    for (size_t i = 0; i < length; i++)
    {
        assert(searchUNORDEREDSET(table, integers[i]) != NULL);
    }

    for (size_t i = 0; i < length; i++)
    {
        freeINTEGER(integers[i]);
    }

    free(integers);

    return 0;
}
