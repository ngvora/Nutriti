#include "ROW.h"
#include <assert.h>
#include <stdlib.h>

struct row
{
    INTEGER* id;
    STRING* name;
    STRING* vendor;
    STRING* energyUnits;
    STRING* carbUnits;
    STRING* fatUnits;
    STRING* protein;
    STRING* servingSize;
    STRING* servingSuffix;
    STRING* weirdServingSize;
    STRING* weirdServingSuffix;
};

ROW* newROW(size_t id, STRING* name, STRING* vendor, STRING* energyUnits, STRING* carbUnits, STRING* fatUnits,
    STRING* protein, STRING* servingSize, STRING* servingSuffix, STRING* weirdServingSize, STRING* weirdServingSuffix)
{
    assert(name != NULL && vendor != NULL);

    ROW* row = malloc(sizeof(ROW));
    row->id = newINTEGER(id);
    row->name = name;
    row->vendor = vendor;
    row->energyUnits = energyUnits;
    row->carbUnits = carbUnits;
    row->fatUnits = fatUnits;
    row->protein = protein;
    row->servingSize = servingSize;
    row->servingSuffix = servingSuffix;
    row->weirdServingSize = weirdServingSize;
    row->weirdServingSuffix = weirdServingSuffix;

    return row;
}

ROW* readROW(FILE* fp)
{
    STRING* idStr = readSTRING(fp, "~", NULL);
    STRING* name = readSTRING(fp, "~", NULL);
    STRING* vendor = readSTRING(fp, "~", NULL);
    STRING* energyUnits = readSTRING(fp, "~", NULL);
    STRING* carbUnits = readSTRING(fp, "~", NULL);
    STRING* fatUnits = readSTRING(fp, "~", NULL);
    STRING* protein = readSTRING(fp, "~", NULL);
    STRING* servingSize = readSTRING(fp, "~", NULL);
    STRING* servingSuffix = readSTRING(fp, "~", NULL);
    STRING* weirdServingSize = readSTRING(fp, "~", NULL);

    int last;

    STRING* weirdServingSuffix = readSTRING(fp, "\n", &last);

    size_t id;
    sscanf(getSTRING(idStr), "%zu", &id);
    freeSTRING(idStr);

    ROW* row = newROW(id, name, vendor, energyUnits, carbUnits, fatUnits, protein, servingSize, servingSuffix, weirdServingSize, weirdServingSuffix);

    if (last == EOF) {
        freeROW(row);
        return NULL;
    }

    return row;
}

INTEGER* getROWid(ROW* row)
{
    assert(row != NULL);
    return row->id;
}

STRING* getROWname(ROW* row)
{
    assert(row != NULL);
    return row->name;
}

STRING* getROWvendor(ROW* row)
{
    assert(row != NULL);
    return row->vendor;
}

void printROW(ROW* row, FILE* file)
{
    assert(row != NULL);
    assert(file != NULL);

    fprintf(file, "ID: %zu\tName: %s\tVendor: %s\tEnergy: %s\tCarb Units: %s\tFat Units: %s\t"
    "Protein Units: %s\tServing Size: %s %s\tAlt. Serving Size: %s %s", getINTEGER(row->id), getSTRING(row->name),
    getSTRING(row->vendor), getSTRING(row->energyUnits), getSTRING(row->carbUnits), getSTRING(row->fatUnits),
    getSTRING(row->protein), getSTRING(row->servingSize), getSTRING(row->servingSuffix), getSTRING(row->weirdServingSize),
    getSTRING(row->weirdServingSuffix));
}

void freeROW(void* rowVoid)
{
    ROW* row = rowVoid;
    assert(row != NULL);
    freeINTEGER(row->id);
    freeSTRING(row->name);
    freeSTRING(row->vendor);
    freeSTRING(row->energyUnits);
    freeSTRING(row->carbUnits);
    freeSTRING(row->fatUnits);
    freeSTRING(row->protein);
    freeSTRING(row->servingSize);
    freeSTRING(row->servingSuffix);
    freeSTRING(row->weirdServingSize);
    freeSTRING(row->weirdServingSuffix);
    
    free(row);
}
