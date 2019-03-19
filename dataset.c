#include "dataset.h"
#include <assert.h>

/* Linked list structure */
       typedef struct list
       {
           char *string;
           int index;
           struct list *next
       } list_t ;
   

// Creates a DATASET from the filename
DATASET* newDATASET(char* filename)
{
    DATASET* dataset = malloc(sizeof(DATASET));
    assert(dataset != NULL);

    FILE* file = fopen(filename, "r");

    // loop to read food types into dataset

    fclose(file);
    return dataset;
}

// Get number of elements in dataset
size_t sizeDATASET(DATASET* dataset)
{
    assert(dataset != NULL);
    return dataset->length;
}

// Get item at index
void* getDATASETindex(DATASET* dataset, size_t index)
{
    assert(dataset != NULL);
    assert(index < dataset->length);

    return dataset->elements[index];
}


// Deallocate the memory associated with a DATASET
// Can only be called when no QUERY_RESULTs for the DATASET exist.
void freeDATASET(DATASET* dataset)
{
    for (size_t i = 0; i < dataset->length; i++)
    {
        // delete food info at dataset->elements[i]
    }

    freeDATASET(dataset);
}
