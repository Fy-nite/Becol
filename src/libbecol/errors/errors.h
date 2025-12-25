#include <stdbool.h>

#ifndef BECOL_ERRORS
#define BECOL_ERRORS

typedef enum {
    BECOL_ERROR_GENERIC,
    BECOL_ERROR_PARSING
} ErrorCode;

typedef struct {
    ErrorCode err;
    char* message;
} Error;

extern bool errorFlag;
extern Error* currentError;

void BecolReportError(ErrorCode err, char* message);
bool BecolIsError();
void BecolClearError();
void BecolPrintError();

#endif
