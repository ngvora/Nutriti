extern "C" {
#include "UNORDEREDSET.h"
}
#include <cassert>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>

#include <unordered_set>

typedef struct
{
    int value;
} INTEGER;

INTEGER* newINTEGER(int value)
{
    INTEGER* i = (INTEGER*)malloc(sizeof(INTEGER));
    assert(i != NULL);
    i->value = value;
    return i;
}

bool compareINTEGER(void* i1, void* i2)
{
    assert(i1 != NULL);
    assert(i2 != NULL);

    return ((INTEGER*)i1)->value == ((INTEGER*)i2)->value;
}

void freeINTEGER(void* i)
{
    assert(i != NULL);
    free(i);
}

size_t hashINTEGER(void* i)
{
    assert(i != NULL);
    return (size_t)((INTEGER*)i)->value;
}

void* cloneINTEGER(void* i)
{
    assert(i != NULL);
    return newINTEGER(((INTEGER*)i)->value);
}

void printINTEGER(void* i, void* unused)
{
    (void)unused;

    if (i == NULL)
        printf("_ ");
    else
        printf("%d ", ((INTEGER*)i)->value);
}

struct hash
{
    size_t operator()(int i)
    {
        return (size_t)i;
    }
};


bool same(const std::unordered_set<int, hash>& test, UNORDEREDSET* table)
{
    struct data {
        const std::unordered_set<int, hash>* test;
        bool valid;
    };

    data x;
    x.test = &test;
    x.valid = true;

    foreachUNORDEREDSET(table, [](void* current, void* test) {
        if (current == NULL)
            return;

        int value = ((INTEGER*)current)->value;
        if (!((data*)test)->test.contains(value))
            ((data*)test)->valid = false;
    }, &x);

    if (!x.valid)
    {
        printf("UNORDERED set contains elements not in std::unordered_set");
    }

    for (auto element : test)
    {
        
    }
}

int main(void)
{
    UNORDEREDSET* table = newUNORDEREDSET(hashINTEGER, compareINTEGER, freeINTEGER);

    

    std::unordered_set<int, hash> test;

    for (size_t i = 0; i < 1000000; i++)
    {
        if (rand() % 8 == 0 && test.size() != 0)
        {
            int key = *test.begin();
            test.erase(test.begin());

            INTEGER* temp = newINTEGER(key);
            deleteUNORDEREDSET(table, temp, NULL);
            freeINTEGER(temp);
        }

        else
        {
            int next = rand();
            test.insert(next);
            insertUNORDEREDSET(table, newINTEGER(next));
        }
    }



    return 0;
}
