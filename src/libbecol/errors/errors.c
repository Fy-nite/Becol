#include <stdbool.h>
#include <stdio.h>
#include "errors.h"
#include "../memory/mem.h"

bool errorFlag = false;
Error* currentError;

void ReportError(ErrorCode err, char* message) {
    if (errorFlag) {
        printf("Error reported while error already existed\n");
        PrintError();
        ClearError();
    }
    errorFlag = true;
    currentError = BecolMalloc(sizeof(Error));
    currentError->err = err;
    currentError->message = BecolStrMalloc(message); // we cannot guarantee that the string 
                                                     // will be avaliable forever so we just
                                                     // copy it
}

bool IsError() {
    return errorFlag;
}

void ClearError() {
    errorFlag = false;
    BecolFree(currentError);
}

void PrintError() {
    if (errorFlag)
        printf("err: code: %d msg: \"%s\"\n", currentError->err, currentError->message); // TODO: actually good printing
}
