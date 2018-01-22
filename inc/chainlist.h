#ifndef HSW_CHAINLIST_H
#define HSW_CHAINLIST_H

#include <stdlib.h>

/*
 * Add allocate memory for a new element at the end of a chainlist
 *
 * chainlist	Pointer to a chainlist
 * eme
 */
void* chainlist_add(void** chainlist, size_t elem_size);

void* chainlist_get(void* chainlist, int index);

#endif

