#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc(void *ptr, size_t new_size, size_t old_size){
    if(ptr == NULL){
        return malloc(new_size);
    }

    if(new_size == 0){
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);
    if(new_ptr == NULL){
        return NULL;
    }

    size_t copy_size = (new_size < old_size) ? new_size : old_size;
    memcpy(new_ptr, ptr, copy_size);

    free(ptr);
    return new_ptr;
}