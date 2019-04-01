#include "UNORDEREDSET.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tableelement
{
    void* data;
    size_t hash;
} TABLEELEMENT;

static char reservedAddress;

#define CHAIN_ELEMENT &reservedAddress

struct unorderedset
{
    size_t bufferLength;
    size_t size;
    size_t filledElements;
    float maxLoad;
    TABLEELEMENT* elements;

    size_t (*hash)(void*);
    bool(*cmp)(void*, void*);
    void (*deleter)(void*);
};

static size_t findNextIndex(UNORDEREDSET* set, size_t index)
{
    assert(set != NULL);
    index %= set->bufferLength;

    for (size_t i = 0; i < set->bufferLength; i++)
    {
	void* data = set->elements[(i + index) % set->bufferLength].data;

        if (data == NULL || data == CHAIN_ELEMENT)
            return (i + index) % set->bufferLength;
    }

    assert(false);
}

static ptrdiff_t findItem(UNORDEREDSET* set, void* key, ptrdiff_t* firstEmpty)
{
    assert(set != NULL);
    assert(key != NULL);

    size_t hash = set->hash(key);
    size_t index = hash % set->bufferLength;

    if (firstEmpty != NULL)
        *firstEmpty = -1;

    for (size_t i = index; set->elements[i % set->bufferLength].data != NULL; i++)
    {
        assert(i != index + set->bufferLength);
        TABLEELEMENT* current = &set->elements[i % set->bufferLength];

        if ((current->data == NULL || current->data == CHAIN_ELEMENT) && firstEmpty != NULL)
        {
            *firstEmpty = i % set->bufferLength;
            firstEmpty = NULL;
        }

        if (!(current->data == NULL || current->data == CHAIN_ELEMENT) && current->hash == hash && set->cmp(current->data, key))
            return i % set->bufferLength;
    }

    return -1;
}

// Creates a DATASET from the filename
UNORDEREDSET* newUNORDEREDSET(size_t(*hash)(void*), bool(*cmp)(void*, void*), void(*deleter)(void*))
{
    assert(hash != NULL);
    assert(cmp != NULL);

    UNORDEREDSET* set = (UNORDEREDSET*)malloc(sizeof(UNORDEREDSET));
    assert(set != NULL);
    set->bufferLength = 2;
    set->size = 0;
    set->filledElements = 0;
    set->maxLoad = 0.5;

    set->elements = (TABLEELEMENT*)malloc(set->bufferLength * sizeof(TABLEELEMENT));
    assert(set->elements != NULL);

    for (size_t i = 0; i < set->bufferLength; i++)
        set->elements[i].data = NULL;

    set->hash = hash;
    set->cmp = cmp;
    set->deleter = deleter;

    return set;
}

bool insertUNORDEREDSET(UNORDEREDSET* set, void* data)
{
    assert(set != NULL);
    assert(data != NULL);

    if (searchUNORDEREDSET(set, data) != NULL)
        return false;

    size_t hash = set->hash(data);
    size_t index = findNextIndex(set, hash);

    // Double table length when load factor is too high
    if (set->elements[index].data != CHAIN_ELEMENT)
    {
        if ((float)(set->filledElements + 1) / set->bufferLength > set->maxLoad)
        {
            reserveUNORDEREDSET(set, (set->filledElements + 1));
            index = findNextIndex(set, hash);
        }

        set->filledElements++;
    }

    set->size++;
    set->elements[index].data = data;
    set->elements[index].hash = hash;

    return true;
}

void* searchUNORDEREDSET(UNORDEREDSET* set, void* key)
{
    assert(set != NULL);
    assert(key != NULL);

    ptrdiff_t next;
    ptrdiff_t index = findItem(set, key, &next);

    if (index == -1)
        return NULL;

    if (next != -1)
    {
        set->elements[next].data = set->elements[index].data;
        set->elements[next].hash = set->elements[index].hash;
        set->elements[index].data = CHAIN_ELEMENT;

        if (set->elements[(index + 1) % set->bufferLength].data == NULL)
            set->elements[index].data = NULL;

        index = next;
    }

    return set->elements[index].data;
}

bool deleteUNORDEREDSET(UNORDEREDSET* set, void* key, void** relocation)
{
    assert(set != NULL);
    assert(key != NULL);

    ptrdiff_t index = findItem(set, key, NULL);

    if (index == -1)
    {
        if (relocation != NULL)
            *relocation = NULL;

        return false;
    }

    else
    {
        if (relocation != NULL)
            *relocation = set->elements[index].data;
        else if (set->deleter != NULL)
            set->deleter(set->elements[index].data);
        
        set->size--;
        set->elements[index].data = CHAIN_ELEMENT;

        if (set->elements[(index + 1) % set->bufferLength].data == NULL)
        {
            set->elements[index].data = NULL;
            set->filledElements--;
        }

        return true;
    }
}

// Return load factor limit
float getUNORDEREDSETmaxLoad(UNORDEREDSET* set)
{
    assert(set != NULL);
    return set->maxLoad;
}

// Change load factor limit (0 < maxLoad < 1)
void setUNORDEREDSETmaxLoad(UNORDEREDSET* set, float maxLoad)
{
    assert(set != NULL);
    set->maxLoad = maxLoad;
}

// Get current load factor
float getUNORDEREDSETloadFactor(UNORDEREDSET* set)
{
    assert(set != NULL);
    return (float)set->filledElements / set->bufferLength;
}

// Hint about number of elements in table
void reserveUNORDEREDSET(UNORDEREDSET* set, size_t n)
{
    assert(set != NULL);

    n /= set->maxLoad;

    if (n <= set->bufferLength)
        return;
    
    size_t bitIndex = sizeof(size_t) * CHAR_BIT - 1;

    // Find first bit set
    while ((((size_t)1 << bitIndex) & n) == 0)
        bitIndex--;
    
    // Power of two
    size_t newBufferLength = (size_t)1 << bitIndex != n ? (size_t)1 << (bitIndex + 1) : (size_t)1 << bitIndex;
    assert(newBufferLength >= n);

    TABLEELEMENT* newElements = (TABLEELEMENT*)malloc(newBufferLength * sizeof(TABLEELEMENT));
    assert(newElements != NULL);

    for (size_t i = 0; i < newBufferLength; i++)
        newElements[i].data = NULL;

    // Turn old table into empty table with newBufferLength elements
    size_t oldLength = set->bufferLength;
    TABLEELEMENT* oldElements = set->elements;
    set->bufferLength = newBufferLength;
    set->elements = newElements;
    set->size = 0;
    set->filledElements = 0;

    for (size_t i = 0; i < oldLength; i++)
    {
        if (oldElements[i].data != NULL && oldElements[i].data != CHAIN_ELEMENT)
            insertUNORDEREDSET(set, oldElements[i].data);
    }

    free(oldElements);
}

// Allow table to reallocate itself to reduce load factor if necessary
void rehashUNORDEREDSET(UNORDEREDSET* set)
{
    assert(set != NULL);

    if (set->size == set->filledElements)
        return;

    // Insert all into new unordered set. Since there are no deletions, all spaces are full - the load factor is minimized
    UNORDEREDSET* next = newUNORDEREDSET(set->hash, set->cmp, NULL);

    for (size_t i = 0; i < set->bufferLength; i++)
    {
        void* data = set->elements[i].data;
        
        if (data != NULL && data != CHAIN_ELEMENT)
            insertUNORDEREDSET(next, data);
    }

    // Swap arrays
    set->filledElements = next->filledElements;
    TABLEELEMENT* tempBuffer = set->elements;
    set->elements = next->elements;
    next->elements = tempBuffer;

    size_t tempLength = set->bufferLength;
    set->bufferLength = next->bufferLength;
    next->bufferLength = tempLength;

    freeUNORDEREDSET(next);
}

// Get number of elements in set
size_t sizeUNORDEREDSET(UNORDEREDSET* set)
{
    assert(set != NULL);
    return set->size;
}

// Deallocate the set and its contents
void freeUNORDEREDSET(UNORDEREDSET* set)
{
    assert(set != NULL);

    if (set->deleter != NULL)
    {
        for (size_t i = 0; i < set->bufferLength; i++)
            if (set->elements[i].data != NULL && set->elements[i].data != CHAIN_ELEMENT)
                set->deleter(set->elements[i].data);
    }

    free(set->elements);
    free(set);
}

void foreachUNORDEREDSET(UNORDEREDSET* set, void(*fn)(void* data, void* extraParams), void* extraParams)
{
    assert(set != NULL);
    assert(fn != NULL);

    for (size_t i = 0; i < set->bufferLength; i++)
    {
        if (set->elements[i].data != NULL && set->elements[i].data != CHAIN_ELEMENT)
            fn(set->elements[i].data, extraParams);
    }
}

void statisticsUNORDEREDSET(UNORDEREDSET* set, size_t* maxChainLength, float* avgWalk)
{
	assert(set != NULL);
	size_t maxChain = 0;
	size_t walkTotal = 0;
	size_t currentChainLength = 0;

	for (size_t i = 0; i < set->bufferLength; i++)
	{
		if (set->elements[i].data == NULL)
		{
			if (currentChainLength > maxChain)
				maxChain = currentChainLength;
			walkTotal += (currentChainLength * (currentChainLength + 1)) / 2;
			currentChainLength = 0;
		}

		else
			currentChainLength++;
	}


	if (currentChainLength > maxChain)
		maxChain = currentChainLength;
	walkTotal += (currentChainLength * (currentChainLength + 1)) / 2;
	currentChainLength = 0;

	if (maxChainLength != NULL)
		*maxChainLength = maxChain;

	if (avgWalk != NULL)
		*avgWalk = walkTotal / (float)set->bufferLength;
}
