#include <stdbool.h>

#ifndef BECOL_ERRORS
#define BECOL_ERRORS

typedef enum {
    BECOL_ERROR_GENERIC
} ErrorCode;

typedef struct {
    ErrorCode err;
    char* message;
} Error;

extern bool errorFlag;
extern Error* currentError;

void ReportError(ErrorCode err, char* message);
bool IsError();
void ClearError();
void PrintError();

#endif
