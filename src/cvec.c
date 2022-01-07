/*
 * Copyright (c) 2022 Dmytro Zykov
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "cvec.h"

#include <stdlib.h>
#include <string.h>

typedef unsigned long long u64;

struct _cvec {
  int capacity;
  int size;
  int stride;
  void *array;
};

static void _cvec_resize(cvec vec) {
  if (!vec) {
    return;
  }

  vec->capacity *= CVEC_RESIZE_FACTOR;
  void *arr = realloc(vec->array, vec->capacity * vec->stride);
  if (!arr) {
    return;
  } else {
    vec->array = arr;
  }
}

cvec _cvec_create(int capacity, int stride) {
  cvec vec = (cvec)malloc(sizeof(struct _cvec));
  if (!vec) {
    return NULL;
  }

  vec->capacity = capacity;
  vec->size = 0;
  vec->stride = stride;
  int *arr = (int *)malloc(vec->capacity * vec->stride);
  if (!arr) {
    return NULL;
  }
  memset(arr, 0, vec->capacity * vec->stride);
  vec->array = (void *)arr;

  return vec;
}

void _cvec_push_back(cvec vec, void *value_ptr) {
  if (!vec) {
    return;
  }

  if (vec->size >= vec->capacity) {
    _cvec_resize(vec);
  }

  u64 addr = (u64)(vec->array);
  addr += vec->size * vec->stride;
  memcpy((void *)addr, value_ptr, vec->stride);
  vec->size++;
}

void _cvec_insert(cvec vec, int index, void *value_ptr) {
  if (!vec || index < 0 || index >= vec->size) {
    return;
  }

  if (vec->size >= vec->capacity) {
    _cvec_resize(vec);
  }

  u64 addr = (u64)vec->array;
  memcpy((void *)(addr + ((index + 1) * vec->stride)),
  (void *)(addr + (index * vec->stride)),
  ((vec->size - index) * vec->stride));
  memcpy((void *)(addr + (index * vec->stride)), value_ptr, vec->stride);
  vec->size++;
}

void _cvec_set_at(cvec vec, int index, void *value_ptr) {
  if (!vec || index < 0 || index >= vec->size) {
    return;
  }

  memcpy((void *)(((u64)vec->array) + (index * vec->stride)), value_ptr, vec->stride);
}

void *_cvec_at(cvec vec, int index) {
  if (!vec || index < 0 || index >= vec->size) {
    return NULL;
  }

  return (void *)(((u64)(vec->array)) + (index * vec->stride));
}

void *_cvec_raw(cvec vec) {
  if (!vec) {
    return NULL;
  }

  return vec->array;
}

void cvec_destroy(cvec vec) {
  if (!vec) {
    return;
  }

  free(vec->array);
  free(vec);
}

int cvec_size(cvec vec) {
  if (!vec) {
    return 0;
  }

  return vec->size;
}

void cvec_pop_back(cvec vec) {
  if (!vec) {
    return;
  }

  memset((void *)((u64)vec->array + ((vec->size - 1) * vec->stride)), 0, vec->stride);
  vec->size--;
}

void cvec_erase(cvec vec, int index) {
  if (!vec || index < 0 || index >= vec->size) {
    return;
  }

  u64 addr = (u64)vec->array;
  memcpy((void *)(addr + (index * vec->stride)), 
    (void *)(addr + ((index + 1) * vec->stride)), 
    (vec->size - index) * vec->stride);
  vec->size--;
}