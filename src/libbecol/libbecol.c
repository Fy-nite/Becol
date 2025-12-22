// libbecol. The library to parse and run becol code

#include <stdio.h>
#include "defines.h"
#include "libbecol.h"
#include "memory/mem.h"

void BecolInit() {
    return; // TODO: things
}

char* BecolVersion() {
    return (VERSION " " SOURCE "+" COMMIT);
}

void BecolModuleSearchPaths(char* paths[], int paths_len) {
    for (int i=0;i<paths_len;i++) {
        printf("Loading modules from %s\n", paths[i]);
    }
}

void BecolRun(char* str) {

}

void BecolCleanup() {
    BecolFreeAll();
}
