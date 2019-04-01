#include "dynarr.h"

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

struct da
{
	// Pointer to physical array
	void** buffer;
	// User-defined functions for output and deallocation
	void (*deallocator)(void*);

	// Size of logical array
	size_t size;
	// Size of physical array
	size_t capacity;

};

DA* newDA(void (*deallocator)(void*))
{
	DA* da = malloc(sizeof(DA));
	assert(da != NULL);

	da->deallocator = deallocator;
	da->size = 0;
	da->capacity = 1;
	da->buffer = malloc(sizeof(void*));
	assert(da->buffer != NULL);

	return da;
}

void insertDA(DA* items, size_t index, void* value)
{
	assert(items != NULL);
	assert(items->size >= index && index >= 0);

	// Check if reallocation is necessary
	if (items->size == items->capacity)
	{
		items->capacity *= 2;
		items->buffer = realloc(items->buffer, items->capacity * sizeof(void*));
		assert(items->buffer != NULL);
	}

	for (ptrdiff_t i = items->size; i > index; i--)
		items->buffer[i] = items->buffer[i - 1];

	items->size++;
	items->buffer[index] = value;
}

void* removeDA(DA* items, size_t index)
{
	assert(items != NULL);
	assert(items->size > index && index >= 0);

	// Shrinking is necessary if the size is less than 1 / 4 of capacity
	if (items->capacity != 1 && 4 * (items->size - 1) < items->capacity)
	{
		// If the array will be empty, there is a special case specifying that the capacity shall be 1
		items->capacity = items->size == 1 ? 1 : items->capacity / 2;
		items->buffer = realloc(items->buffer, items->capacity * sizeof(void*));
		assert(items->buffer != NULL);
	}

	void* old = items->buffer[index];

	for (ptrdiff_t i = index; i < items->size - 1; i++)
		items->buffer[i] = items->buffer[i + 1];

	items->size--;

	return old;
}

void unionDA(DA* recipient, DA* donor)
{
	assert(recipient != NULL);
	assert(donor != NULL);

	// Self-unions are avoided
	if (recipient == donor)
		return;

	for (ptrdiff_t i = 0; i < donor->size; i++)
		setDA(recipient, sizeDA(recipient), getDA(donor, i));

	free(donor->buffer);
	donor->size = 0;
	donor->capacity = 1;
	donor->buffer = malloc(sizeof(void*));
}

void* getDA(DA* items, size_t index)
{
	assert(items != NULL);
	assert(index < items->size && index >= 0);

	return items->buffer[index];
}

void* setDA(DA* items, size_t index, void* value)
{
	assert(items != NULL);
	assert(index <= items->size && index >= 0);

	// Special case triggers insertion
	if (index == items->size)
	{
		insertDA(items, items->size, value);
		return NULL;
	}

	void* old = items->buffer[index];
	items->buffer[index] = value;

	return old;
}

size_t sizeDA(DA* items)
{
	assert(items != NULL);

	return items->size;
}

void freeDA(DA* items)
{
	assert(items != NULL);

	if (items->deallocator != NULL)
	{
		for (ptrdiff_t i = 0; i < items->size; i++)
			items->deallocator(items->buffer[i]);
	}

	if (items->buffer != NULL)
		free(items->buffer);

	free(items);
}
