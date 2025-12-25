#include <stdbool.h>
#include <stdio.h>
#include "errors.h"
#include "../memory/mem.h"

bool errorFlag = false;
Error* currentError;

void BecolReportError(ErrorCode err, char* message) {
    if (errorFlag) {
        printf("Error reported while error already existed\n");
        BecolPrintError();
        BecolClearError();
    }
    errorFlag = true;
    currentError = BecolMalloc(sizeof(Error));
    currentError->err = err;
    currentError->message = BecolStrMalloc(message); // we cannot guarantee that the string 
                                                     // will be avaliable forever so we just
                                                     // copy it
}

bool BecolIsError() {
    return errorFlag;
}

void BecolClearError() {
    errorFlag = false;
    BecolFree(currentError->message);
    BecolFree(currentError);
}

void BecolPrintError() {
    if (errorFlag)
        printf("err: code: %d msg: \"%s\"\n", currentError->err, currentError->message); // TODO: actually good printing
}
