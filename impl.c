#include "array.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct array {
  size_t sizeof_element;
  size_t capacity;
  size_t size;

  char data[];
};

static struct array *array_realloc(struct array *a, size_t new_capacity) {
  new_capacity = new_capacity ? new_capacity : a->capacity * 2;
  return realloc(a, sizeof(*a) + a->sizeof_element * new_capacity);
}

struct array *array_create(size_t sizeof_element, size_t initial_size) {
  size_t capacity = initial_size ? 2 * initial_size : 128;
  struct array *a = malloc(sizeof(*a) + sizeof_element * capacity);
  *a = (struct array){
      .sizeof_element = sizeof_element,
      .capacity = capacity,
      .size = initial_size,
  };
  return a;
}

void array_destroy(struct array *a) { free(a); }

size_t array_size(struct array const *a) { return a->size; }

void *array_at(struct array *a, size_t idx) {
  return &a->data[idx * a->sizeof_element];
}

void const *array_cat(struct array const *a, size_t idx) {
  return &a->data[idx * a->sizeof_element];
}

void array_foreach(struct array *a, void (*func)(void *)) {
  for (size_t i = 0; i < a->sizeof_element * a->size; i += a->sizeof_element) {
    func(&a->data[i]);
  }
}

void array_cforeach(struct array const *a, void (*func)(void const *)) {
  for (size_t i = 0; i < a->sizeof_element * a->size; i += a->sizeof_element) {
    func(&a->data[i]);
  }
}

#define debug(x, t) printf("%s => " t "\n", #x, x)

struct array *array_insert(struct array *a, size_t idx) {
  assert(idx <= a->size);

  // check capacity
  if (a->capacity < a->size + 1) {
    a = array_realloc(a, 0);
  }

  memmove(array_at(a, idx + 1), array_at(a, idx), a->size * a->sizeof_element);
  a->size++;

  return a;
}

void array_remove(struct array *a, size_t idx) {
  assert(idx < a->size);

  // check size
  assert(a->size);

  memmove(array_at(a, idx), array_at(a, idx + 1), a->size * a->sizeof_element);

  a->size--;
}
