#include "string.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "dynarr.h"


struct string
{
    char* buffer;
};

STRING* newSTRING(const char* buffer)
{
    assert(buffer != NULL);
    STRING* str = malloc(sizeof(STRING));
    assert(str != NULL);
    str->buffer = malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(str->buffer, buffer);
    assert(str->buffer != NULL);
    return str;
}

STRING* cloneSTRING(STRING* str)
{
    assert(str != NULL);
    return newSTRING(str->buffer);
}

STRING* readSTRING(FILE* file, const char* delim, int* last)
{
    assert(file != NULL);
    assert(delim != NULL);

    DA* buffer = newDA(NULL);

    int ch = fgetc(file);

    while (ch != EOF && strchr(delim, ch) == NULL)
    {
        insertDAback(buffer, (void*)(intptr_t)ch);
        ch = fgetc(file);
    }

    if (last != NULL)
        *last = ch;

    char* data = malloc((sizeDA(buffer) + 1) * sizeof(char));

    for (size_t i = 0; i < sizeDA(buffer); i++)
    {
        data[i] = (char)(intptr_t)getDA(buffer, i);
    }

    data[sizeDA(buffer)] = '\0';
    freeDA(buffer);
    STRING* str = newSTRING(data);
    free(data);
    return str;
}

size_t sizeSTRING(STRING* str)
{
    assert(str != NULL);
    return strlen(str->buffer);
}

size_t hashSTRING(void* str)
{
    assert(str != NULL);
    size_t hash = 5381;

    char* data = ((STRING*)str)->buffer;
    unsigned char current;

    while ((current = *++data))
    {
        hash = ((hash << 5) + hash) + current;
    }

    return hash;
}

bool compareSTRING(void* str1, void* str2)
{
    assert(str1 != NULL && str2 != NULL);
    return strcmp(((STRING*)str1)->buffer, ((STRING*)str2)->buffer) == 0;
}

const char* getSTRING(STRING* str)
{
    assert(str != NULL);
    return str->buffer;
}

char getSTRINGchar(STRING* str, size_t n)
{
    assert(str != NULL);
    assert(n < strlen(str->buffer));
    return str->buffer[n];
}

char setSTRINGchar(STRING* str, size_t n, char ch)
{
    assert(str != NULL);
    assert(n < strlen(str->buffer));
    char old = str->buffer[n];
    str->buffer[n] = ch;
    return old;
}

void freeSTRING(void* str)
{
    assert(str != NULL);
    free(((STRING*)str)->buffer);
    free(str);
}

