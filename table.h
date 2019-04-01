#ifndef INCLUDED_TABLE_H
#define INCLUDED_TABLE_H

#include <stdio.h>
#include "dynarr.h"
#include "ROW.h"
#include "string.h"
#include "UNORDEREDMAP.H"

typedef struct table TABLE;

TABLE* newTABLE(size_t columns, STRING** columnNames, size_t(**hash)(void*),
    bool(**cmp)(void*, void*), void(**deleter)(void*), bool* primaryKey, bool(**constraintChecker)(void*));

size_t sizeTABLE(TABLE* table);

size_t rowLengthTABLE(TABLE* table);

bool createTABLE(TABLE* table, size_t length, void** row);

DA* readTABLE(TABLE* table, STRING* query, STRING* index);

bool updateTABLE(TABLE* table, STRING* query, STRING* index, UNORDEREDMAP* updates);

bool deleteTABLE(TABLE* table, STRING* query, STRING* index);

void freeTABLE(TABLE* table);

#endif
