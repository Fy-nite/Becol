#ifndef LIBBECOL
#define LIBBECOL

void BecolInit();
char* BecolVersion();

void BecolModuleSearchPaths(char* paths[], int paths_len);
void BecolRun(char* str);

void BecolCleanup();

#endif
