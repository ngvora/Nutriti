typedef struct queryresult QUERYRESULT;

#ifndef INCLUDED_QUERYRESULT_H
#define INCLUDED_QUERYRESULT_H

#include <stddef.h>
#include "dataset.h"

// Create new query result containing everything in the dataset.
QUERYRESULT* newQUERYRESULT(DATASET* dataset);

// Create new entry in query result. void* corresponds to some data structure describing a food.
void addQUERYRESULT(QUERYRESULT* result, void* item);
// Retrieve info from query result. Makes a new query result containing only the elements where predicate returns true.
// Corresponds with filter operation from functional programming.
QUERYRESULT* selectQUERYRESULT(QUERYRESULT* result, int(*predicate)(void*));
// Update info in query result. Applies update to every item in the query result.
// Corresponds with map operation from functional programming. Performed in place
void updateQUERYRESULT(QUERYRESULT* result, void(*update)(void*));
// Delete info from query result. Deletes every item where predicate returns true.
// Opposite of select.
void deleteQUERYRESULT(QUERYRESULT* result, int(*predicate)(void*));

// Deallocate query result from memory.
void freeQUERYRESULT(QUERYRESULT* result);

#endif
