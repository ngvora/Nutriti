#ifndef DA_INCLUDED
#define DA_INCLUDED

#include <stdio.h>

/*
 * Dynamically resizable array.
 * Insertion or removal at a constant distance from the end is O(1) (amortized)
 * Space complexity for n elements is O(n)
 * The type is incomplete to hide implementation details.
 *
 * */

typedef struct da DA;

// DA constructor which returns an empty DA
extern DA* newDA(void (*deallocator)(void*));
// Inserts an element at index in a DA. Insertion a constant distance from the back shall have O(1) time complexity (amortized)
extern void insertDA(DA* items, size_t index, void* value);
// Removes and retrieves an element at index in a DA. Removal at a constant distance from the back shall O(1) time complexity (amortized)
extern void* removeDA(DA* items, size_t index);
// Removes all elements of donor and appends them into recipient. If the size of donor is n, unionDA shall have O(n) time complexity (amortized)
extern void* getDA(DA* items, size_t index);
// Mofies element at index in a DA and retrieves the old value in O(1) time
extern void* setDA(DA* items, size_t index, void* value);
// Gets size of the DA in O(1) time
extern size_t sizeDA(DA* items);
// If the debug level is not positive, prints the contents of the array. Otherwise, the remaining capacity is included.
// In either case, if a user-defined print function is supplied, it shall be used.
extern void freeDA(DA* items);
// Inserts value at the back of a DA in O(1) time (amortized)
#define insertDAback(items, value) insertDA(items, sizeDA(items), value)
// Removes value at the back of a DA in O(1) time (amortized)
#define removeDAback(items) removeDA(items, sizeDA(items) - 1)

#endif