#include <stdlib.h>
#include <string.h>

#include "chainlist.h"

void* chainlist_add(void** next_elem, size_t elem_size)
{
    while(*next_elem != NULL)
    {
        next_elem = *next_elem;
    }

    *next_elem = malloc(elem_size);
    memset(*next_elem, 0, elem_size);

    return *next_elem;
}

