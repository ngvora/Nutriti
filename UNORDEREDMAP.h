typedef struct unorderedmap UNORDEREDMAP;

#include <stdbool.h>
#include <stddef.h>

#ifndef INCLUDED_UNORDEREDMAP_H
#define INCLUDED_UNORDEREDMAP_H

// Creates an unordered map
UNORDEREDMAP* newUNORDEREDMAP(size_t(*keyHash)(void*), bool(*keyCmp)(void*, void*), void(*keyDeleter)(void*), void(*valueDeleter)(void*));

// Replaces entry associated with key with value. If oldValue is not old, the previous value is written (or NULL). If oldValue is NULL, the previous value is deleted with valueDeleter
bool insertUNORDEREDMAP(UNORDEREDMAP* map, void* key, void* value, void** oldValue);

// Finds if there is an entry associated with key, and if so returns true. Writes to valuePtr if valuePtr is not NULL and the key is present.
void* searchUNORDEREDMAP(UNORDEREDMAP* map, void* key, void** keyPtr);

// returns true if item removed or false if item not removed
bool deleteUNORDEREDMAP(UNORDEREDMAP* map, void* key, void** oldKey, void** oldValue);

// Return load factor limit
float getUNORDEREDMAPmaxLoad(UNORDEREDMAP* map);

// Change load factor limit (0 < maxLoad < 1)
void setUNORDEREDMAPmaxLoad(UNORDEREDMAP* map, float maxLoad);

// Get current load factor
float getUNORDEREDMAPloadFactor(UNORDEREDMAP* map);

// Hint about number of elements in table
void reserveUNORDEREDMAP(UNORDEREDMAP* map, size_t n);

// Allow table to reallocate itself to reduce load factor if necessary
void rehashUNORDEREDMAP(UNORDEREDMAP* map);

// Get number of elements in set
size_t sizeUNORDEREDMAP(UNORDEREDMAP* map);

// Deallocate the set and its contents
void freeUNORDEREDMAP(UNORDEREDMAP* map);

// Calls fn on every key-value pair in hte map
void foreachUNORDEREDMAP(UNORDEREDMAP* map, void(*fn)(void* key, void* value, void* extraParams), void* extraParams);

// Get hash table statistics
void statisticsUNORDEREDMAP(UNORDEREDMAP* map, size_t* maxChainLength, float* avgWalk);

#endif
