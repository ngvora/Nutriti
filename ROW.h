#ifndef INCLUDED_ROW_H
#define INCLUDED_ROW_H

#include <stdio.h>
#include "string.h"
#include "INTEGER.h"

typedef struct row ROW;

ROW* newROW(size_t id, STRING* name, STRING* vendor, STRING* energyUnits, STRING* carbUnits, STRING* fatUnits,
    STRING* protein, STRING* servingSize, STRING* servingSuffix, STRING* weirdServingSize, STRING* weirdServingSuffix);

ROW* readROW(FILE* fp);

INTEGER* getROWid(ROW* row);

STRING* getROWname(ROW* row);

STRING* getROWvendor(ROW* row);

void printROW(ROW* row, FILE* file);

void freeROW(void* row);

#endif
