#include "dataset.h"
#include <assert.h>

/* Food struct */
       typedef struct fooddata
       {   int productid;
           char *productname;
           char *manu;
           float energyunits;
           float carbunits;
           float fatunits;
           float proteinunits;
           float servingsizegml;
           char gml[10];
           float servingsize;
           char ssunits[15];
       }  
   

// Creates a DATASET from the filename
DATASET* newDATASET(char* filename)
{
    DATASET* dataset = malloc(sizeof(DATASET));
    assert(dataset != NULL);

    FILE* file = fopen(food_nutrient_db, "r");

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
