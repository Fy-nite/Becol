#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "mem.h"

// these function should be used instead of malloc and free
// because these function help keep track of malloed memory
// to help debug memory leaks

// This is not supposted to be a custom malloc

// All errors in here instantly crash the runtime because
// error handling needs to malloc memory so we would be in
// a infinite loop
// try to malloc -> report error -> try to malloc -> report error -> etc

MemoryChunk* rootMemory = NULL;

// append a chunk to the end of the list
void addChunk(MemoryChunk* chunk) {
    chunk->next = NULL;
    if (rootMemory == NULL) {
        chunk->prev = NULL;
        rootMemory = chunk;
    } else {
        MemoryChunk* end_chunk = rootMemory;
        while (end_chunk->next != NULL) {
            end_chunk = end_chunk->next;
        }
        end_chunk->next = chunk;
        chunk->prev = end_chunk;
    }
}

bool canFreeChunk(void* addr) { // Try to find chunk, if found then delete chunk and return true. Else return false
    if (rootMemory == NULL) {
        return false;
    }
    MemoryChunk* chunk = rootMemory;
    if (chunk->next == NULL) {
        if (chunk->addr != addr) {
            return false;
        }
        free(chunk);
        rootMemory = NULL;
        return true;
    }
    while (chunk->addr != addr) {
        if (chunk->next != NULL)
            chunk = chunk->next;
        else
            return false;
    }
    if (chunk == rootMemory) {
        rootMemory = chunk->next;
    }
    if (chunk->prev != NULL) chunk->prev->next = chunk->next;
    if (chunk->next != NULL) chunk->next->prev = chunk->prev;
    free(chunk);
    return true;
}

// malloc memory and append chunk
void* BecolMalloc(int size) {
    void* mem = malloc(size);
    MemoryChunk* new_chunk = malloc(sizeof(MemoryChunk));
    if (mem == NULL || new_chunk == NULL) {
        perror("FATAL: Failed to malloc memory");
        exit(1);
    }
    new_chunk->size = size;
    new_chunk->addr = mem;
    addChunk(new_chunk);
    return mem;
}

// free memory and delete chunk
void BecolFree(void* mem) {
    if (mem == NULL)
        return;
    if (canFreeChunk(mem))
        free(mem);
    else {
        printf("FATAL: Tried to free memory at addres %p but no MemoryChunk exists for that address\n", mem);
        exit(1);
    }
}

// read the .h file for a description
char* BecolStrMalloc(char* str) {
    int len = strlen(str);
    char* ret = BecolMalloc(len+1);
    strcpy(ret, str);
    return ret;
}

void BecolFreeAll() {
    MemoryChunk* c = rootMemory;
    MemoryChunk* tmp;
    while (c != NULL) {
        printf("WARNING: unfreed memory at %p with size %d\n", c->addr, c->size);
        free(c->addr);
        //printf("%d\n", *(char*)c->addr); // hacky solution to get address sanitizer to
                                           // output stack trace of malloc cause use after free
        tmp = c->next;
        free(c);
        c = tmp;
    }
}
