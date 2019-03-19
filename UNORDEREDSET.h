typedef struct unorderedset UNORDEREDSET;

#include <stddef.h>

#ifndef INCLUDED_UNORDEREDSET_H
#define INCLUDED_UNORDEREDSET_H

// Creates a DATASET from the filename
UNORDEREDSET* newUNORDEREDSET(size_t(*hash)(void*), bool(*cmp)(void*, void*),
    size_t(*probeIndex)(void* data, size_t n), void(*deleter)(void*));

void insertUNORDEREDSET(UNORDEREDSET* set, void* data);

void* searchUNORDEREDSET(UNORDEREDSET* set, void* key);

void deleteUNORDEREDSET(UNORDEREDSET* set, void* key);

// Return load factor limit
float getUNORDEREDSETmaxLoad(UNORDEREDSET* set);

// Change load factor limit (0 < maxLoad < 1)
void setUNORDEREDSETmaxLoad(UNORDEREDSET* set, float maxLoad);

// Get current load factor
float getUNORDEREDSETLoadFactor(UNORDEREDSET* set);

// Hint about number of elements in table
void reserveUNORDEREDSET(UNORDEREDSET* set, size_t n);

// Allow table to reallocate itself to reduce load factor if necessary
void rehashUNORDEREDSET(UNORDEREDSET* set);

// Get number of elements in set
size_t sizeDATASET(UNORDEREDSET* set);

// Deallocate the set and its contents
void freeUNORDEREDSET(UNORDEREDSET* set);

#endif
