#ifndef BECOL_MEM
#define BECOL_MEM

typedef struct MemoryChunk {
    int size;
    void* addr;
    struct /*<- gay*/ MemoryChunk* next;
    struct MemoryChunk* prev;
} MemoryChunk;

extern MemoryChunk* rootMemory;

void* BecolMalloc(int size);
void  BecolFree(void* mem);
char* BecolStrMalloc(char* str); // mallocs and strcpys a string so 
                                 // that we can make sure a string
                                 // exists later
void BecolFreeAll(); // used for program cleanup. Really shouldn't 
                     // do anything but if something wasn't freed
                     // then this would free it

#endif
