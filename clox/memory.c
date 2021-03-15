#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t old_size, size_t new_size) {
    // if old size is 0 then free allocation
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    // otherwise reallocate to smaller or larger memory block
    void* result = realloc(pointer, new_size);
    return result;
}