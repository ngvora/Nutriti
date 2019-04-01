#ifndef INCLUDED_STRING_H
#define INCLUDED_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct string STRING;

STRING* newSTRING(const char* buffer);

STRING* cloneSTRING(STRING* str);

STRING* upperSTRING(STRING* str);

STRING* readSTRING(FILE* file, const char* delim, int* last);

size_t sizeSTRING(STRING* str);

size_t hashSTRING(void* str);

bool compareSTRING(void* str1, void* str2);

const char* getSTRING(STRING* str);

char getSTRINGchar(STRING* str, size_t n);

char setSTRINGchar(STRING* str, size_t n, char ch);

void freeSTRING(void* str);

#endif
