typedef struct dataset DATASET;

#include <stdio.h>
#include "queryresult.h"

#ifndef INCLUDED_DATASET_H
#define INCLUDED_DATASET_H

// Creates a DATASET from the filename
DATASET* newDATASET(char* filename);

// Get number of elements in dataset
size_t sizeDATASET(DATASET* dataset);

// Get item at index
void* getDATASETindex(DATASET* dataset, size_t index);

// Deallocate the memory associated with a DATASET
// Can only be called when no QUERY_RESULTs for the DATASET exist.
void freeDATASET(DATASET* dataset);

#endif
