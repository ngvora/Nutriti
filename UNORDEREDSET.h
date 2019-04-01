typedef struct unorderedset UNORDEREDSET;

#include <stdbool.h>
#include <stddef.h>

#ifndef INCLUDED_UNORDEREDSET_H
#define INCLUDED_UNORDEREDSET_H

// Creates a DATASET from the filename
UNORDEREDSET* newUNORDEREDSET(size_t(*hash)(void*), bool(*cmp)(void*, void*), void(*deleter)(void*));

bool insertUNORDEREDSET(UNORDEREDSET* set, void* data);

void* searchUNORDEREDSET(UNORDEREDSET* set, void* key);

bool deleteUNORDEREDSET(UNORDEREDSET* set, void* key, void** relocation);

// Return load factor limit
float getUNORDEREDSETmaxLoad(UNORDEREDSET* set);

// Change load factor limit (0 < maxLoad < 1)
void setUNORDEREDSETmaxLoad(UNORDEREDSET* set, float maxLoad);

// Get current load factor
float getUNORDEREDSETloadFactor(UNORDEREDSET* set);

// Hint about number of elements in table
void reserveUNORDEREDSET(UNORDEREDSET* set, size_t n);

// Allow table to reallocate itself to reduce load factor if necessary
void rehashUNORDEREDSET(UNORDEREDSET* set);

// Get number of elements in set
size_t sizeUNORDEREDSET(UNORDEREDSET* set);

// Deallocate the set and its contents
void freeUNORDEREDSET(UNORDEREDSET* set);

void foreachUNORDEREDSET(UNORDEREDSET* set, void(*fn)(void* data, void* extraParams), void* extraParams);

void statisticsUNORDEREDSET(UNORDEREDSET* set, size_t* maxChainLength, float* avgWalk);

#endif