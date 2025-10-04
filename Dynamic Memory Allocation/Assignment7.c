#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment){
    void *original = malloc(size + alignment - 1 + sizeof(void *));
    if (original == NULL) return NULL;

    uintptr_t addr = (uintptr_t)original + sizeof(void *);
    uintptr_t aligned = (addr + alignment - 1) & ~(uintptr_t)(alignment - 1);

    ((void **)aligned)[-1] = original;

    return (void *)aligned;
}

void aligned_free(void *ptr){
    if (ptr == NULL) return NULL;
    void *original = ((void **)ptr)[-1];
    free(original);
}