#ifndef HSW_CHAINLIST_H
#define HSW_CHAINLIST_H

#include <stdlib.h>

void* chainlist_add(void** chainlist, size_t elem_size);

void* chainlist_get(void* chainlist, int index);

#endif

