#include "table.h"
#include <assert.h>
#include <stdlib.h>

typedef struct {
    UNORDEREDMAP* index;
    size_t (*hash)(void*);
    bool (*cmp)(void*, void*);
    void (*deleter)(void*);
    bool unique;
    bool (*constraint)(void*);
    size_t columnNo;
} COLUMN;

void freeCOLUMN(void* info);

// Describes entry in table and lists things that reference it
typedef struct row
{
    size_t length;
    DA* items;
    DA* references;
} ROW;

struct table
{
    UNORDEREDMAP* columnInfo;
    DA* columnList;
    DA* uniqueKeys;
    UNORDEREDSET* rows;
    size_t size;
};

TABLE* newTABLE(size_t columns, STRING** columnNames, size_t(**hash)(void*),
    bool(**cmp)(void*, void*), void(**deleter)(void*), bool* uniqueKey, bool(**constraintChecker)(void*))
{
    TABLE* table = malloc(sizeof(TABLE));
    assert(table != NULL);

    table->size = 0;
    table->uniqueKeys = newDA(NULL);
    table->columnList = newDA(NULL);
    table->rows = newDA(NULL);
    table->columnInfo = newUNORDEREDMAP(hashSTRING, compareSTRING, freeSTRING, freeCOLUMN);

    for (size_t i = 0; i < columns; i++)
    {
        COLUMN* column = malloc(sizeof(COLUMN));
        assert(column != NULL);
        column->columnNo = i;

        if (hash[i] != NULL)
            column->index = newUNORDEREDMAP(hash[i], cmp[i], deleter[i], NULL);
        column->hash = hash[i];
        column->unique = uniqueKey[i];

        // Primary keys must be hashable for indexing
        if (column->unique && column->hash == NULL) {
            freeTABLE(table);

            if (column->index != NULL) {
                freeUNORDEREDMAP(column->index);
            }

            return NULL;
        }

        if (column->unique) {
            insertDAback(table->uniqueKeys, column->index);
        }

        column->constraint = constraintChecker[i];
        column->deleter = deleter[i];
        column->cmp = cmp[i];

        void* oldColumn;
        insertUNORDEREDMAP(table->columnInfo, columnNames[i], column, &oldColumn);

        if (oldColumn != NULL) {
            freeTABLE(table);
            freeCOLUMN(oldColumn);
            return NULL;
        }

        insertDAback(table->columnList, column);
    }

    return table;
}

size_t sizeTABLE(TABLE* table)
{
    assert(table != NULL);
    return table->size;
}

size_t rowLengthTABLE(TABLE* table)
{
    return sizeUNORDEREDMAP(table->columnInfo);
}

bool createTABLE(TABLE* table, DA* row)
{
    assert(table != NULL);

    if (sizeDA(row) != sizeUNORDEREDMAP(table->columnInfo))
        return false;

    for (size_t i = 0; i < sizeDA(row); i++)
    {
        COLUMN* columnInfo = table->columnList[i];

        if (columnInfo->hash && searchUNORDEREDMAP(columnInfo->index, getDA(row, i), NULL) != NULL)
            return false;
    }
    
    for (size_t i = 0; i < sizeDA(row); i++) {
        COLUMN* column = getDA(table->columnList, i);

        if (column->unique)
            insertUNORDEREDMAP(column->index, getDA(row, i), row, NULL);
    }

    worry about management here
}

DA* readTABLE(TABLE* table, STRING* query, STRING* index) {
    assert(table != NULL && query != NULL && index != NULL);

    COLUMN* column = searchUNORDEREDMAP(table->columnInfo, query, NULL);

    if (column == NULL || column->index == NULL)
        return NULL;
    
    DA* row = searchUNORDEREDMAP(column->index, query, NULL);
    return row;
}

typedef struct updateinfo
{
    TABLE* table;
    bool valid;
    DA* row;
} UPDATEINFO;

void updateRow(void* indexVoid, void* newValue, void* infoVoid)
{
    STRING* index = indexVoid;
    UPDATEINFO* info = infoVoid;

    COLUMN* column = searchUNORDEREDMAP(info->table->columnInfo, index, NULL);

    assert(column != NULL);

    if (column->index == NULL) {
        setDA(info->row, column->index, newValue);
    }

    else {
        void* oldRow;
        deleteUNORDEREDMAP(column->index, getDA(info->row, column->index), NULL, &oldRow);
        assert(oldRow == info->row);
        insertUNORDEREDMAP(column->index, newValue, info->row, NULL);
        setDA(info->row, column->index, newValue);
    }   
}

void checkRow(void* indexVoid, void* newValue, void* infoVoid)
{
    STRING* index = indexVoid;
    UPDATEINFO* info = infoVoid;

    if (!info->valid)
        return;

    COLUMN* column = searchUNORDEREDMAP(info->table->columnInfo, index, NULL);

    if (column == NULL) {
        info->valid = false;
        return;
    }

    if (column->unique && searchUNORDEREDMAP(column->index, newValue, NULL) != NULL) {
        info->valid = false;
        return;
    }

    if (column->constraint != NULL && !column->constraint(newValue)) {
        info->valid = false;
        return;
    }   
}

bool updateTABLE(TABLE* table, STRING* query, STRING* index, UNORDEREDMAP* updates)
{
    assert(table != NULL && query != NULL && index != NULL && updates != NULL);

    COLUMN* column = searchUNORDEREDMAP(table->columnInfo, index, NULL);

    if (column == NULL)
        return false;
    
    DA* row = searchUNORDEREDMAP(column, query, NULL);

    UPDATEINFO info;
    info.table = table;
    info.row = row;
    info.valid = true;

    foreachUNORDEREDMAP(updates, checkRow, &info);

    if (!info.valid)
        return false;
    
    foreachUNORDEREDMAP(updates, updateRow, &info);
    return true;
}

bool deleteTABLE(TABLE* table, STRING* query, STRING* index)
{
    assert(table != NULL && query != NULL && index != NULL);

    COLUMN* column = searchUNORDEREDMAP(table->columnInfo, index, NULL);

    if (column == NULL)
        return false;
    
    
}

void freeTABLE(TABLE* table)
{
    assert(table != NULL);
}
