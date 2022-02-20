#ifndef ARRAY_H_
#define ARRAY_H_

#include <stddef.h>

struct array *array_create(size_t sizeof_element, size_t initial_size);
void array_destroy(struct array *);

size_t array_size(struct array const *);

void *array_at(struct array *, size_t idx);
void const *array_cat(struct array const *, size_t idx);

void array_foreach(struct array *, void (*func)(void *));
void array_cforeach(struct array const *, void (*func)(void const *));

// shifts the array such that idx is a new empty slot
// this function might reallocate, so the new array
// is returned
struct array *array_insert(struct array *, size_t idx);
// shifts the array removing the data at idx
void array_remove(struct array *, size_t idx);

#endif // ARRAY_H_
