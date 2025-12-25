#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "tokens.h"
#include "../memory/mem.h"
#include "../errors/errors.h"

// utility file for stuff relating to Token stuff.

// Allocating tokens
Token* BecolMallocToken() {
    Token* token = BecolMalloc(sizeof(Token));
    token->text = NULL;
    token->next = NULL;
    token->info = NULL;
    return token;
}

void BecolFreeToken(Token* token) {
    if (token == NULL)
        return;
    Token* curr = token;
    Token* tmp;
    while (curr->next) {
        tmp = curr;
        curr = curr->next;
        BecolFree(tmp->text);
        BecolFree(tmp->info);
        BecolFree(tmp);
    }
    BecolFree(curr->text);
    BecolFree(curr->info);
    BecolFree(curr);
}


// Allocating Programs / Getting a program reference
Program* BecolGetProgram(char* prog) {
    Program* ret = BecolMalloc(sizeof(Program));
    ret->next_token = NULL;
    ret->next_token_start = 0;
    ret->text = BecolStrMalloc(prog);
    ret->at_end = false;
    return ret;
}

void BecolFreeProgram(Program* prog) {
    BecolFree(prog->text);
    if (prog->next_token) BecolFreeToken(prog->next_token);
    BecolFree(prog);
}

void BecolParseOneCharToken(Token* tok) {
    switch (tok->text[0]) {
        case '{':
            tok->type = TOKEN_LEFT_CURLY_BRACKET;
            break;
        case '}':
            tok->type = TOKEN_RIGHT_CURLY_BRACKET;
            break;
        case '\n':
            tok->type = TOKEN_NEWLINE;
            break;
        case '+':
            tok->type = TOKEN_PLUS;
            break;
        case '-':
            tok->type = TOKEN_MINUS;
            break;
        case '*':
            tok->type = TOKEN_ASTRISK;
            break;
        case '/':
            tok->type = TOKEN_FORWARD_SLASH;
            break;
        case '%':
            tok->type = TOKEN_PERCENT;
            break;
        case '=':
            tok->type = TOKEN_EQUAL;
            break;
        case '>':
            tok->type = TOKEN_LESS_THAN;
            break;
        case '<':
            tok->type = TOKEN_GREATER_THAN;
            break;
        default:
            BecolReportError(BECOL_ERROR_PARSING, "Failed to parse one character token");
    }
}

// possiblilies: >= <= !=
void BecolParseTwoCharToken(Token* tok) {
    if (tok->text[0] == '>' && tok->text[1] == '=')
        tok->type = TOKEN_GREATER_OR_EQUAL;
    else if (tok->text[0] == '<' && tok->text[1] == '=')
        tok->type = TOKEN_LESS_OR_EQUAL;
    else if (tok->text[0] == '!' && tok->text[1] == '=')
        tok->type = TOKEN_NOTEQUAL;
    else
        BecolReportError(BECOL_ERROR_PARSING, "Failed to parse two character token");
}

bool BecolTryParseNumber(Token* tok) {
    char* text = tok->text;
    bool is_float = false;
    if (text[0] == '-')
        text++;
    while (*text != '\0') {
        char c = *text;
        if ((c < 48 || c > 57) && c != '.')
            return false;
        if (c == '.')
            is_float = true;
        text++;
    }
    tok->type = is_float ? TOKEN_NUMBER : TOKEN_FLOAT;
    return true;
}

bool BecolTryParseString(Token* tok) {
    if (tok->text[0] == '"' && tok->text[strlen(tok->text)-1] == '"') {
        tok->type = TOKEN_STRING;
        return true;
    }
    return false;
}

void BecolGetTokenType(Token* tok) {
    int len = strlen(tok->text);
    if (len == 0)
        BecolReportError(BECOL_ERROR_PARSING, "Cannot parse token of len zero");
    else if (BecolTryParseNumber(tok)) {}
    else if (BecolTryParseString(tok)) {}
    else if (len == 1)
        BecolParseOneCharToken(tok);
    else if (len == 2)
        BecolParseTwoCharToken(tok);
    else {
        BecolReportError(BECOL_ERROR_PARSING, "Failed to parse token");
    }
    if (BecolIsError())
        return;
}

// Getting tokens
/*Token* BecolNextToken(Program* prog) {
    if (prog->at_end){
        BecolReportError(BECOL_ERROR_PARSING, "Tried to get token when at end of string");
        return NULL;}
    char* ptr = prog->text+prog->next_token_start;
    char c = *ptr;
    int size = 0;
    // get to start of token
    while (c == ' ' || c == '\t') {
        c = *(ptr+=1);
    }
    char* tok_start = ptr;
    bool in_str = false; // is in double quotes
    // get size of token
    while (((c != ' ' && c != '\t') || in_str) && c != '\0') {
        size++;
        if (c == '"')
            in_str = !in_str;
        c = *(ptr+=1);
    }
    if (in_str) {
        BecolReportError(BECOL_ERROR_PARSING, "String never closed");
        return NULL;
    }
    // create and copy toen info
    Token* tok = BecolMallocToken(size);
    memcpy(tok->text, tok_start, size);
    tok->text[size] = 0;
    //printf("%s\n", tok->text);
    tok->addr = tok_start - prog->text;
    tok->next = NULL;
    BecolGetTokenType(tok); // get the type of token
    if (BecolIsError()) { // error stuff
        BecolFreeToken(tok);
        return NULL;
    }
    // jump to end for the token_start value thing
    while (c == ' ' || c == '\t') {
        c = *(ptr+=1);
    }
    prog->next_token_start = ptr - prog->text;
    if (c == '\0') prog->at_end = true;
    return tok;
}*/

Token* BecolMallocCharToken(char c, Program* prog, TokenType type) {
    Token* tok = BecolMallocToken();
    tok->text = BecolMalloc(2);
    tok->text[0] = c;
    tok->text[1] = 0;
    tok->type = type;
    tok->addr = prog->next_token_start+1;
    prog->next_token_start++;
    return tok;
}

Token* BecolMallocTwoCharToken(char c, char c2, Program* prog, TokenType type) {
    Token* tok = BecolMallocToken();
    tok->text = BecolMalloc(3);
    tok->text[0] = c;
    tok->text[1] = c2;
    tok->text[2] = 0;
    tok->type = type;
    tok->addr = prog->next_token_start+=2;
    return tok;
}

// Getting tokens
Token* BecolNextToken(Program* prog) {
    if (!prog->at_end && prog->text[prog->next_token_start] == '\0') {
        Token* tok = BecolMallocToken();
        tok->type = TOKEN_EOF;
        tok->addr = prog->next_token_start;
        prog->at_end = true;
        return tok;
    }
    else if (prog->at_end) {
        prog->at_end = true;
        BecolReportError(BECOL_ERROR_PARSING, "Tried to get token when at end of string");
        return NULL;
    }
    int status = 0; // 0 - normal, 1 - number, 2 - string
    int i=0;
    char c;
    char* ptr = prog->text+prog->next_token_start;
    while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
        {prog->next_token_start++; ptr++;}
    for (;(c=ptr[i])!=0;i++) {
        if (status == 2) { // string
            if (c == '"') {
                Token* tok = BecolMallocToken();
                tok->type = TOKEN_STRING;
                tok->text = BecolMalloc(i);
                memcpy(tok->text, prog->text+prog->next_token_start+1, i-1);
                tok->text[i-1] = 0;
                tok->addr = prog->next_token_start;
                prog->next_token_start+=i+1;
                return tok;
            }
        }
        else if (status == 1) { // number
            bool is_float = false;
            int left = 0; // left of .
            int right = 0; // right of .
            while ((c >= '0' && c <= '9') || c == '.') {
                if (c == '.')
                    is_float = true;
                else {
                    if (is_float)
                        {right *= 10; right += c-'0';}
                    else
                        {left *= 10; left += c-'0';}
                }
                c=ptr[++i];
            }
            Token* tok = BecolMallocToken();
            tok->type = is_float ? TOKEN_FLOAT : TOKEN_NUMBER;
            tok->text = BecolMalloc(i+1);
            if (is_float) {
                double num = 0;
                num = right;
                while (num >= 1) num /= 10;
                num += left;
                snprintf(tok->text, i+1, "%f", num);
                tok->info = BecolMalloc(sizeof(num));
                memcpy(tok->info, &num, sizeof(num));
            } else {
                snprintf(tok->text, i+1, "%d", left);
                tok->info = BecolMalloc(sizeof(left));
                memcpy(tok->info, &left, sizeof(left));
            }
            prog->next_token_start += i;
            return tok;
        }
        else if (status == 0) {
            switch (c) {
                case '"':
                    status = 2; // string
                    break;
                case '0' ... '9':
                    i--;
                    status = 1; // number
                    break;
                case '{':
                    return BecolMallocCharToken(c, prog, TOKEN_LEFT_CURLY_BRACKET);
                case '}':
                    return BecolMallocCharToken(c, prog, TOKEN_RIGHT_CURLY_BRACKET);
                case '+':
                    return BecolMallocCharToken(c, prog, TOKEN_PLUS);
                case '-':
                    return BecolMallocCharToken(c, prog, TOKEN_MINUS);
                case '*':
                    return BecolMallocCharToken(c, prog, TOKEN_ASTRISK);
                case '/':
                    return BecolMallocCharToken(c, prog, TOKEN_FORWARD_SLASH);
                case '%':
                    return BecolMallocCharToken(c, prog, TOKEN_PERCENT);
                case '=':
                    return BecolMallocCharToken(c, prog, TOKEN_EQUAL);
                case '>':
                    if (ptr[i+1] == '=')
                        return BecolMallocTwoCharToken(c, ptr[i+1], prog, TOKEN_GREATER_OR_EQUAL);
                    return BecolMallocCharToken(c, prog, TOKEN_GREATER_THAN);
                case '<':
                    if (ptr[i+1] == '=')
                        return BecolMallocTwoCharToken(c, ptr[i+1], prog, TOKEN_LESS_OR_EQUAL);
                    return BecolMallocCharToken(c, prog, TOKEN_LESS_THAN);
                case '!':
                    if (ptr[i+1] == '=')
                        return BecolMallocTwoCharToken(c, ptr[i+1], prog, TOKEN_NOTEQUAL);
                    return BecolMallocCharToken(c, prog, TOKEN_NOT);
                case '(':
                    return BecolMallocCharToken(c, prog, TOKEN_LEFT_PARENTHESIS);
                case ')':
                    return BecolMallocCharToken(c, prog, TOKEN_RIGHT_PARENTHESIS);
                default:
                    BecolReportError(BECOL_ERROR_PARSING, "Unexpected char");
                    return NULL;
            }
        }
    }
    BecolReportError(BECOL_ERROR_PARSING, "Reached end of program without finding a token");
    return NULL;
}

Token* BecolPeekToken(Program* prog);


