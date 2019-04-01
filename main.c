#include "ROW.h"
#include "UNORDEREDMAP.H"
#include "STRING.h"
#include "dynarr.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct database
{
    UNORDEREDMAP* idIndex;
    UNORDEREDMAP* nameIndex;
    UNORDEREDMAP* vendorIndex;
    UNORDEREDMAP* keywords;
} DATABASE;

void keywordSplit(STRING* name, ROW* row, UNORDEREDMAP* index);
void keywordSplitRemove(STRING* name, ROW* row, UNORDEREDMAP* index);

DATABASE initializeDATABASE(void);
DATABASE openDATABASE(FILE* fp);
void writeDATABASE(DATABASE db, FILE* fp);
void freeDATABASE(DATABASE db);

bool fileExists(const char* filename);
bool existingDiaryName(STRING* name);
bool addToDiary(STRING* name);
void deleteDiaryName(STRING* name);
void printIndex(void);

void insertDATABASE(DATABASE* database, DA* results);
void removeDATABASE(DATABASE* database, DA* results);

DA* uniqueDA(DA* input);
STRING* getDiary(DATABASE* database);
void useDiary(STRING* diaryName, DATABASE* database, DATABASE* dataset, FILE* out, FILE* in);

void printDiary(DATABASE* database);

int main(void)
{
    FILE* temp = fopen("./diary_list.txt", "a");
    if (temp != NULL)
        fclose(temp);

    DATABASE dataset;
    FILE* datasetFile = fopen("food_nutrient_db.csv", "r+");

    if (!fileExists("diary_list.txt"))
    {
        printf("Error: cannot find diary list file. Please rerun the program and try again.\n");
        return 1;
    }

    if (datasetFile == NULL) {
        printf("Error: cannot find dataset file.Please make sure you have downloaded the correct dataset file and try again\n");
        return 1;
    }

    dataset = openDATABASE(datasetFile);

    STRING* diaryName = NULL;

    do
    {
        DATABASE currentDiary;
        diaryName = getDiary(&currentDiary);

        if (diaryName == NULL)
            break;

        FILE* file = fopen(getSTRING(diaryName), "r+");

        if (!file) {
            printf("Failed to open diary file\n");
        }

        useDiary(diaryName, &currentDiary, &dataset, NULL, file);
        fclose(file);
        file = fopen(getSTRING(diaryName), "a");

        if (diaryName == NULL) {
            return 1;
        }

        printf("Opened diary %s\n", getSTRING(diaryName));

        useDiary(diaryName, &currentDiary, &dataset, file, stdin);
        fclose(file);
    } while (diaryName != NULL);

    return 0;
}


void keywordSplit(STRING* name, ROW* row, UNORDEREDMAP* index)
{
    char* data = malloc(sizeof(char) * (strlen(getSTRING(name)) + 1));
    char* old = data;

    strcpy(old, getSTRING(name));
    data = strtok(old, " ");

    while ((data = strtok(NULL, " ")) != NULL)
    {
        STRING* keyword = newSTRING(data);

        DA* array = searchUNORDEREDMAP(index, keyword, NULL);

        if (array == NULL)
        {
            array = newDA(freeSTRING);
            insertDAback(array, row);
            insertUNORDEREDMAP(index, keyword, array, NULL);
        }

        else
        {
            insertDAback(array, row);
            freeSTRING(keyword);
        }
    }

    free(old);
}

DATABASE initializeDATABASE(void)
{
    DATABASE database;
    database.nameIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, NULL);
    database.vendorIndex = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, NULL);
    database.keywords = newUNORDEREDMAP(hashSTRING, compareSTRING, freeSTRING, (void(*)(void*))freeDA);
    database.idIndex = newUNORDEREDMAP(hashINTEGER, compareINTEGER, NULL, NULL);

    return database;
}

DATABASE openDATABASE(FILE* fp)
{
    DATABASE database = initializeDATABASE();

    while (!feof(fp))
    {
        ROW* row = readROW(fp);

        if (row == NULL) {
            break;
        }

        insertUNORDEREDMAP(database.nameIndex, getROWname(row), row, NULL);
        insertUNORDEREDMAP(database.vendorIndex, getROWname(row), row, NULL);
        insertUNORDEREDMAP(database.idIndex, getROWid(row), row, NULL);
        keywordSplit(getROWname(row), row, database.keywords);
    }
    return database;
}

void freeDATABASE(DATABASE db)
{
    freeUNORDEREDMAP(db.keywords);
    freeUNORDEREDMAP(db.idIndex);
    freeUNORDEREDMAP(db.vendorIndex);
    freeUNORDEREDMAP(db.nameIndex);
}

bool fileExists(const char* filename)
{
    return access(filename, F_OK) != -1;
}

bool existingDiaryName(STRING* name)
{
    assert(name != NULL);

    FILE* list = fopen("diary_list.txt", "r+");

    if (list == NULL)
    {
        printf("Error: could not open diary_list.txt\n");
        return false;
    }

    int last;
    STRING* current = readSTRING(list, "\n", &last);

    while (!feof(list)) {
        if (compareSTRING(current, name)) {
            if (!fileExists(getSTRING(name))) {
                FILE* file = fopen(getSTRING(name), "w");
                fclose(file);
            }

            freeSTRING(current);
            fclose(list);

            return true;
        }

        freeSTRING(current);
        current = readSTRING(list, "\n", &last);
    }

    if (compareSTRING(current, name)) {
        freeSTRING(current);
        fclose(list);

        return true;
    }

    freeSTRING(current);
    fclose(list);
    return false;
}

bool addToDiary(STRING* name)
{
    assert(name != NULL);

    if (!fileExists(getSTRING(name))) {
        FILE* file = fopen(getSTRING(name), "w");
        fclose(file);
    }

    if (existingDiaryName(name)) {
        return true;
    }

    FILE* file = fopen("diary_list.txt", "a+");
    fprintf(file, "%s\n", getSTRING(name));
    fclose(file);

    return true;
}

STRING* getDiary(DATABASE* database)
{
    STRING* quit = newSTRING("quit");
    STRING* delete = newSTRING("delete");
    STRING* open = newSTRING("open");
    STRING* list = newSTRING("list");

    printf("Please input one of the following commands:\n");
    printf("\tdelete <diary>\n");
    printf("\topen <diary>\n");
    printf("\tlist\n");
    printf("\tquit\n");

    STRING* returnValue = NULL;

    while (!feof(stdin))
    {
        int terminator;
        STRING* command = readSTRING(stdin, " \n\t", &terminator);

        if (terminator == EOF)
        {
            freeSTRING(command);
            break;
        }

        if (compareSTRING(command, quit)) {
            freeSTRING(command);
            break;
        }

	else if (compareSTRING(command, list)) {
            printIndex();
        }

	else if (compareSTRING(command, open)) {
            freeSTRING(command);
            STRING* diaryName = readSTRING(stdin, " \t\n", &terminator);

            if (!existingDiaryName(diaryName)) {
                if (fileExists(getSTRING(diaryName))) {
                    printf("Error: file \"%s\" already exists!\n", getSTRING(diaryName));
                    freeSTRING(diaryName);
                }

                else if (!addToDiary(diaryName)) {
                    printf("Failed to create diary \"%s\"\n", getSTRING(diaryName));
                    freeSTRING(diaryName);
                }

                else {
                    returnValue = diaryName;
                    *database = initializeDATABASE();
                    break;
                }
                

            }

            else {
                returnValue = diaryName;
                *database = initializeDATABASE();
                break;
            }
        }

        else if (compareSTRING(command, delete)) {
            freeSTRING(command);
            STRING* diaryName = readSTRING(stdin, " \t\n", &terminator);

            if (!existingDiaryName(diaryName)) {
                printf("Error: diary \"%s\" does not exist. Please try again with the right command.\n", getSTRING(diaryName));
            }

            else {
                deleteDiaryName(diaryName);
            }

            freeSTRING(diaryName);
        }

        else
        {
            printf("Command \"%s\" not recognized\n", getSTRING(command));
            freeSTRING(command);
        }
        
    }

    freeSTRING(list);
    freeSTRING(quit);
    freeSTRING(delete);
    freeSTRING(open);

    return returnValue;
}

void deleteDiaryName(STRING* name)
{
    FILE* tempFile = NULL;
    char* tempName = NULL;

    while (tempFile == NULL)
    {
        tempName = tmpnam(NULL);
        tempFile = fopen(tempName, "w+");
    }

    FILE* file = fopen("./diary_list.txt", "r+");

    if (file == NULL) {
        printf("Error: could not open diary_list.txt\n");
        fclose(tempFile);
        remove(tempName);
        fclose(file);
        exit(1);
    }

    while (!feof(file))
    {
        int delim;
        STRING* line = readSTRING(file, " \n", &delim);

        if (compareSTRING(line, name))
            continue;
        else if (delim != EOF)
            fprintf(tempFile, "%s%c", getSTRING(line), (char)delim);
        else
            fprintf(tempFile, "%s", getSTRING(line));

        freeSTRING(line);
    }

    if (rename(tempName, "./diary_list.txt") != 0) {
        printf("Error: failed to swap files\n");
        fclose(tempFile);
        remove(tempName);
        fclose(file);
        exit(1);
    }

    if (remove(getSTRING(name)) != 0) {
        printf("Failed to delete diary file \"%s\"\n", getSTRING(name));
        exit(1);
    }
}

void printIndex(void) {
    FILE* list = fopen("./diary_list.txt", "r+");

    if (list == NULL) {
        printf("Error: could not find diary list\n");
        return;
    }

    int current = fgetc(list);

    while (!feof(list))
    {
        putc(current, stdout);
        current = fgetc(list);
    }
}

void useDiary(STRING* diaryName, DATABASE* database, DATABASE* dataset, FILE* out, FILE* in)
{
    STRING* command = NULL;

    while (command == NULL || !feof(in))
    {
        if (in == stdin) {
            printf("Please input one of the following commands:\n");
            printf("\tquery <keyword|id> <key>\n");
            printf("\tdelete <keyword|id> <key>\n");
            printf("\tinsert <keyword|id> <key>\n");
            printf("\tprint (shows current diary items)\n");
            printf("\tquit\n");
        }

        command = readSTRING(in, " \t\n", NULL);

        if (strcmp(getSTRING(command), "print") == 0) {
            freeSTRING(command);
            command = NULL;
            printDiary(database);
            continue;
        }

        else if (strcmp(getSTRING(command), "query") == 0) {
            STRING* name = readSTRING(in, " \t\n", NULL);
            void* query = readSTRING(in, " \t\n", NULL);
            void(*freer)(void*) = freeSTRING;

            UNORDEREDMAP* index = NULL;

            /*if (strcmp(getSTRING(name), "name") == 0) {
                index = dataset->nameIndex;
            }
            else if (strcmp(getSTRING(name), "vendor") == 0) {
                index = dataset->vendorIndex;
            }
            else*/ if (strcmp(getSTRING(name), "keyword") == 0) {
                index = dataset->keywords;
            }
            else if (strcmp(getSTRING(name), "id") == 0) {
                index = dataset->idIndex;
            }
            else if (in == stdin) {
                printf("Error: can not look up on \"%s\"\n", getSTRING(name));
            }

            STRING* upper = upperSTRING(query);
            freeSTRING(query);
            query = upper;

            if (strcmp(getSTRING(name), "id") == 0) {
                size_t v;
                sscanf(getSTRING((STRING*)query), "%zu", &v);
                freeSTRING(query);
                query = newINTEGER(v);
                freer = freeINTEGER;
            }

            freeSTRING(command);
            freeSTRING(name);

            if (index == NULL) {
                continue;
            }

            DA* results = NULL;

            if (index == dataset->keywords) {
                results = searchUNORDEREDMAP(index, query, NULL);

                DA* next = newDA(NULL);

                if (results != NULL) {
                    for (size_t i = 0; i < sizeDA(results); i++) {
                        insertDAback(next, getDA(results, i));
                    }
                }

                results = next;
            }
            
            else {
                results = newDA(NULL);
                void* row = searchUNORDEREDMAP(index, query, NULL);

                if (row != NULL) {
                    insertDAback(results, row);
                }
            }

            if (results == NULL || sizeDA(results) == 0) {
                if (in == stdin)
                    printf("No results found\n");
            }

            else {
                if (in == stdin)
                    printf("Found %zu results\n", sizeDA(results));
                DA* unique = uniqueDA(results);
                freeDA(results);
                results = unique;

                for (size_t i = 0; i < sizeDA(results); i++) {
                    printROW(getDA(results, i), stdout);
                    printf("\n");
                }
            }

            if (results != NULL) {
                freeDA(results);
            }

            freer(query);
        }

        else if (strcmp(getSTRING(command), "insert") == 0) {
            STRING* name = readSTRING(in, " \t\n", NULL);
            void* query = readSTRING(in, " \t\n", NULL);
            void(*freer)(void*) = freeSTRING;

            UNORDEREDMAP* index = NULL;

            /*if (strcmp(getSTRING(name), "name") == 0) {
                index = dataset->nameIndex;
            }
            else if (strcmp(getSTRING(name), "vendor") == 0) {
                index = dataset->vendorIndex;
            }
            else */if (strcmp(getSTRING(name), "keyword") == 0) {
                index = dataset->keywords;
            }
            else if (strcmp(getSTRING(name), "id") == 0) {
                index = dataset->idIndex;
            }
            else if (in == stdin) {
                printf("Error: can not look up on \"%s\"\n", getSTRING(name));
            }

            if (index != NULL && out != NULL) {
                fprintf(out, "%s %s %s\n", getSTRING(command), getSTRING(name), getSTRING((STRING*)query));
            }

            STRING* upper = upperSTRING(query);
            freeSTRING(query);
            query = upper;

            if (strcmp(getSTRING(name), "id") == 0) {
                size_t v;
                sscanf(getSTRING((STRING*)query), "%zu", &v);
                freeSTRING(query);
                query = newINTEGER(v);
                freer = freeINTEGER;
            }

            freeSTRING(command);
            freeSTRING(name);

            if (index == NULL) {
                continue;
            }

            DA* results = NULL;

            if (index == dataset->keywords) {
                results = searchUNORDEREDMAP(index, query, NULL);

                DA* next = newDA(NULL);

                if (results != NULL) {
                    for (size_t i = 0; i < sizeDA(results); i++) {
                        insertDAback(next, getDA(results, i));
                    }
                }

                results = next;
            }
            
            else {
                results = newDA(NULL);
                void* row = searchUNORDEREDMAP(index, query, NULL);

                if (row != NULL) {
                    insertDAback(results, row);
                }
            }

            if (results == NULL || sizeDA(results) == 0) {
                if (in == stdin)
                    printf("No results found\n");
            }

            else {
                if (in == stdin)
                    printf("Found %zu results\n", sizeDA(results));
                insertDATABASE(database, results);
            }

            if (results != NULL) {
                freeDA(results);
            }

            freer(query);
        }

        else if (strcmp(getSTRING(command), "delete") == 0) {
            STRING* name = readSTRING(stdin, " \t\n", NULL);
            void* query = readSTRING(stdin, " \t\n", NULL);
            void(*freer)(void*) = freeSTRING;

            UNORDEREDMAP* index = NULL;

            /*if (strcmp(getSTRING(name), "name") == 0) {
                index = database->nameIndex;
            }
            else if (strcmp(getSTRING(name), "vendor") == 0) {
                index = database->vendorIndex;
            }
            else */if (strcmp(getSTRING(name), "keyword") == 0) {
                index = database->keywords;
            }
            else if (strcmp(getSTRING(name), "id") == 0) {
                index = dataset->idIndex;
            }
            else if (in == stdin) {
                printf("Error: can not look up on \"%s\"\n", getSTRING(name));
            }

            if (index != NULL && out != NULL) {
                fprintf(out, "%s %s %s\n", getSTRING(command), getSTRING(name), getSTRING((STRING*)query));
            }

            if (strcmp(getSTRING(name), "id") == 0) {
                size_t v;
                sscanf(getSTRING((STRING*)query), "%zu", &v);
                freeSTRING(query);
                query = newINTEGER(v);
                freer = freeINTEGER;
            }

            freeSTRING(name);
            freeSTRING(command);

            if (index == NULL) {
                continue;
            }

            DA* results = NULL;

            if (index == database->keywords) {
                results = searchUNORDEREDMAP(index, query, NULL);

                DA* next = newDA(NULL);

                if (results != NULL) {
                    for (size_t i = 0; i < sizeDA(results); i++) {
                        insertDAback(next, getDA(results, i));
                    }
                }

                results = next;
            }
            
            else {
                results = newDA(NULL);
                void* row = searchUNORDEREDMAP(index, query, NULL);

                if (row != NULL) {
                    insertDAback(results, row);
                }
            }

            if (results == NULL || sizeDA(results) == 0) {
                if (in == stdin)
                    printf("No items to delete\n");
            }

            else {
                if (in == stdin)
                    printf("Found %zu results\n", sizeDA(results));
                removeDATABASE(database, results);
            }

            if (results != NULL) {
                freeDA(results);
            }

            freer(query);
        }

        else if (strcmp(getSTRING(command), "quit") == 0) {
            freeSTRING(command);

            if (in == stdin && out != NULL) {
                fprintf(out, "\n");
            }

            return;
        }

        else
        {
            if (in == stdin)
                printf("Command \"%s\" not recognised\n", getSTRING(command));
            freeSTRING(command);
        }
        
    }
}

void diaryPrinter(void* key, void* entry, void* extra) {
    (void)key;
    (void)extra;

    ROW* entryRow = entry;
    printROW(entryRow, stdout);
    printf("\n");
}

void printDiary(DATABASE* database)
{
    foreachUNORDEREDMAP(database->nameIndex, diaryPrinter, NULL);
}

void insertDATABASE(DATABASE* database, DA* results)
{
    assert(database != NULL);
    assert(results != NULL);

    results = uniqueDA(results);

    for (size_t i = 0; i < sizeDA(results); i++) {
        ROW* entry = getDA(results, i);

        if (searchUNORDEREDMAP(database->nameIndex, getROWname(entry), NULL) == NULL) {
            insertUNORDEREDMAP(database->nameIndex, getROWname(entry), entry, NULL);
            insertUNORDEREDMAP(database->vendorIndex, getROWvendor(entry), entry, NULL);
            insertUNORDEREDMAP(database->idIndex, getROWid(entry), entry, NULL);
            keywordSplit(getROWname(entry), entry, database->keywords);
        }
    }
}

void fillUnique(void* key, void* value, void* da) {
    (void)key;
    insertDAback((DA*)da, value);
}

DA* uniqueDA(DA* input) {
    assert(input != NULL);

    UNORDEREDMAP* set = newUNORDEREDMAP(hashSTRING, compareSTRING, NULL, NULL);

    for (size_t i = 0; i < sizeDA(input); i++) {
        insertUNORDEREDMAP(set, getROWname((ROW*)getDA(input, i)), getDA(input, i), NULL);
    }

    DA* unique = newDA(NULL);

    foreachUNORDEREDMAP(set, fillUnique, unique);
    freeUNORDEREDMAP(set);

    return unique;
}

void removeDATABASE(DATABASE* database, DA* results)
{
    assert(database != NULL);
    assert(results != NULL);

    results = uniqueDA(results);

    for (size_t i = 0; i < sizeDA(results); i++) {
        printROW(getDA(results, i), stdout);
        printf("\n");

        ROW* current = getDA(results, i);

        keywordSplitRemove(getROWname(current), current, database->keywords);
        deleteUNORDEREDMAP(database->idIndex, getROWid(current), NULL, NULL);
        deleteUNORDEREDMAP(database->vendorIndex, getROWvendor(current), NULL, NULL);
        deleteUNORDEREDMAP(database->nameIndex, getROWname(current), NULL, NULL);
    }
}

void keywordSplitRemove(STRING* name, ROW* row, UNORDEREDMAP* index)
{
    char* data = malloc(sizeof(char) * (strlen(getSTRING(name)) + 1));
    char* old = data;

    strcpy(old, getSTRING(name));
    data = strtok(old, " ");

    while ((data = strtok(NULL, " ")) != NULL)
    {
        STRING* keyword = newSTRING(data);

        DA* array = searchUNORDEREDMAP(index, keyword, NULL);

        if (array != NULL)
        {
            for (size_t i = 0; i < sizeDA(array); i++) {
                if (getDA(array, i) == row) {
                    removeDA(array, i--);
                }
            }

            if (sizeDA(array) == 0) {
                deleteUNORDEREDMAP(index, keyword, NULL, NULL);
            }
        }
    }

    free(old);
}
