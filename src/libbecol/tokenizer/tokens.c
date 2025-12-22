#include <stddef.h>
#include "tokens.h"
#include "../memory/mem.h"

// utility file for stuff relating to Token stuff.

// Allocating tokens
Token* BecolMallocToken(int text_len) {
    Token* token = BecolMalloc(sizeof(Token));
    return token;
}

void BecolFreeToken(Token* token) {
    Token* curr = token;
    Token* tmp;
    while (curr->next) {
        tmp = curr;
        curr = curr->next;
        BecolFree(tmp);
    }
    BecolFree(curr);
}


// Allocating Programs / Getting a program reference
Program* BecolGetProgram(char* prog) {
    Program* ret = BecolMalloc(sizeof(Program));
    ret->next_token = NULL;
    ret->next_token_start = 0;
    ret->text = BecolStrMalloc(prog);
    return ret;
}

void BecolFreeProgram(Program* prog) {
    BecolFree(prog->text);
    if (prog->next_token) BecolFreeToken(prog->next_token);
    BecolFree(prog);
}


// Getting tokens
Token* BecolNextToken(Program* prog);

Token* BecolPeekToken(Program* prog);


