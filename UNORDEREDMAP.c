#include "UNORDEREDMAP.h"
#include "UNORDEREDSET.h"
#include <assert.h>
#include <stdlib.h>

struct unorderedmap
{
    UNORDEREDSET* set;
    bool (*keyCmp)(void*, void*);
    size_t (*keyHash)(void*);
    void (*keyDeleter)(void*);
    void (*valueDeleter)(void*);
};

typedef struct mapentry
{
    void* key;
    void* value;
    UNORDEREDMAP* map;
} MAPENTRY;

typedef struct paramswrapper
{
    void (*fn)(void*, void*, void*);
    void* extraParams;
} PARAMSWRAPPER;

static bool entryCmp(void* lhsVoid, void* rhsVoid)
{
    MAPENTRY *lhs = lhsVoid, *rhs = rhsVoid;
    return lhs->map->keyCmp(lhs->key, rhs->key);
}

static size_t entryHash(void* entryVoid)
{
    MAPENTRY* entry = entryVoid;
    return entry->map->keyHash(entry->key);
}

static void entryDeleter(void* entryVoid)
{
    MAPENTRY* entry = entryVoid;

    if (entry->map->keyDeleter != NULL)
        entry->map->keyDeleter(entry->key);

    if (entry->map->valueDeleter != NULL)
        entry->map->valueDeleter(entry->value);

    free(entry);
}

void iterateEntry(void* entryVoid, void* extraParams)
{
    MAPENTRY* entry = entryVoid;
    PARAMSWRAPPER* params = extraParams;
    params->fn(entry->key, entry->value, params->extraParams);
}

UNORDEREDMAP* newUNORDEREDMAP(size_t(*keyHash)(void*), bool(*keyCmp)(void*, void*), void(*keyDeleter)(void*), void(*valueDeleter)(void*))
{
    UNORDEREDMAP* map = malloc(sizeof(UNORDEREDMAP));
    assert(map != NULL);
    map->set = newUNORDEREDSET(entryHash, entryCmp, entryDeleter);
    assert(map->set != NULL);
    map->keyHash = keyHash;
    map->keyCmp = keyCmp;
    map->keyDeleter = keyDeleter;
    map->valueDeleter = valueDeleter;

    return map;
}

// Replaces entry associated with key with value. If oldValue is not old, the previous value is written (or NULL). If oldValue is NULL, the previous value is deleted with valueDeleter
bool insertUNORDEREDMAP(UNORDEREDMAP* map, void* key, void* value, void** oldValue)
{
    assert(map != NULL);

    if (oldValue != NULL)
        *oldValue = NULL;

    MAPENTRY entry;
    entry.key = key;
    entry.value = value;
    entry.map = map;

    MAPENTRY* searchResult = searchUNORDEREDSET(map->set, &entry);

    if (searchResult == NULL)
    {
        MAPENTRY* heapEntry = malloc(sizeof(MAPENTRY));
        *heapEntry = entry;
        insertUNORDEREDSET(map->set, heapEntry);

        return true;
    }

    else
    {
        void* old = searchResult->value;

        if (oldValue != NULL)
            *oldValue = old;
        else if (map->valueDeleter != NULL)
            map->valueDeleter(old);

        searchResult->value = value;
        return false;
    }
}

// Finds if there is an entry associated with key, and if so returns true. Writes to valuePtr if valuePtr is not NULL and the key is present.
void* searchUNORDEREDMAP(UNORDEREDMAP* map, void* key, void** keyPtr)
{
    assert(map != NULL);
    MAPENTRY entry;
    entry.key = key;
    entry.value = NULL;
    entry.map = map;

    if (keyPtr != NULL)
        *keyPtr = NULL;

    MAPENTRY* result = searchUNORDEREDSET(map->set, &entry);

    if (result == NULL)
        return NULL;

    if (keyPtr != NULL)
        *keyPtr = result->key;

    return result->value;
}

// returns true if item removed or false if item not removed
bool deleteUNORDEREDMAP(UNORDEREDMAP* map, void* key, void** oldKey, void** oldValue)
{
    assert(map != NULL);

    void* old;

    MAPENTRY entry;
    entry.key = key;
    entry.map = map;

    if (oldKey != NULL)
        *oldKey = NULL;

    if (oldValue != NULL)
        *oldValue = NULL;

    bool result = deleteUNORDEREDSET(map->set, &entry, &old);

    if (!result)
        return false;

    MAPENTRY* oldEntry = old;

    if (oldKey != NULL)
        *oldKey = oldEntry->key;
    else if (map->keyDeleter != NULL)
        map->keyDeleter(oldEntry->key);

    if (oldValue != NULL)
        *oldValue = oldEntry->value;
    else if (map->valueDeleter != NULL)
        map->valueDeleter(oldEntry->value);

    free(oldEntry);
    return true;
}

// Return load factor limit
float getUNORDEREDMAPmaxLoad(UNORDEREDMAP* map)
{
    assert(map != NULL);
    return getUNORDEREDSETmaxLoad(map->set);
}

// Change load factor limit (0 < maxLoad < 1)
void setUNORDEREDMAPmaxLoad(UNORDEREDMAP* map, float maxLoad)
{
    assert(map != NULL);
    setUNORDEREDSETmaxLoad(map->set, maxLoad);
}

// Get current load factor
float getUNORDEREDMAPloadFactor(UNORDEREDMAP* map)
{
    assert(map != NULL);
    return getUNORDEREDSETloadFactor(map->set);
}

// Hint about number of elements in table
void reserveUNORDEREDMAP(UNORDEREDMAP* map, size_t n)
{
    assert(map != NULL);
    reserveUNORDEREDSET(map->set, n);
}

// Allow table to reallocate itself to reduce load factor if necessary
void rehashUNORDEREDMAP(UNORDEREDMAP* map)
{
    assert(map != NULL);
    rehashUNORDEREDSET(map->set);
}

// Get number of elements in set
size_t sizeUNORDEREDMAP(UNORDEREDMAP* map)
{
    assert(map != NULL);
    return sizeUNORDEREDSET(map->set);
}

// Deallocate the set and its contents
void freeUNORDEREDMAP(UNORDEREDMAP* map)
{
    assert(map != NULL);
    freeUNORDEREDSET(map->set);
    free(map);
}

// Calls fn on every key-value pair in hte map
void foreachUNORDEREDMAP(UNORDEREDMAP* map, void(*fn)(void* key, void* value, void* extraParams), void* extraParams)
{
    assert(map != NULL);

    PARAMSWRAPPER params;
    params.extraParams = extraParams;
    params.fn = fn;

    foreachUNORDEREDSET(map->set, iterateEntry, &params);
}

void statisticsUNORDEREDMAP(UNORDEREDMAP* map, size_t* maxChainLength, float* avgWalk)
{
	assert(map != NULL);
	statisticsUNORDEREDSET(map->set, maxChainLength, avgWalk);
}
