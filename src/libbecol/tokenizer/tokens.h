#include <stdbool.h>

#ifndef BECOL_TOKENS
#define BECOL_TOKENS

typedef enum {
    TOKEN_ASK,
    TOKEN_TO,
    TOKEN_TELL,
    TOKEN_FOR,
    TOKEN_WITH,
    TOKEN_AS,
    TOKEN_AND,
    TOKEN_WAIT,
    TOKEN_ACTION,
    TOKEN_DO,
    TOKEN_EVERY,
    TOKEN_WHILE,
    TOKEN_IF,
    TOKEN_LEFT_CURLY_BRACKET,  // {
    TOKEN_RIGHT_CURLY_BRACKET, // }
    TOKEN_IDENTIFIER,
    TOKEN_NEWLINE,             // \n
    TOKEN_PLUS,                // +
    TOKEN_MINUS,               // -
    TOKEN_FORWARD_SLASH,       // /
    TOKEN_ASTRISK,             // *
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_PERCENT,             // %
    TOKEN_EQUAL,               // =
    TOKEN_GREATER_THAN,        // >
    TOKEN_LESS_THAN,           // <
    TOKEN_GREATER_OR_EQUAL,    // >=
    TOKEN_LESS_OR_EQUAL,       // <=
    TOKEN_NOTEQUAL,            // !=
    TOKEN_NOT,                 // !
    TOKEN_LEFT_PARENTHESIS,    // (
    TOKEN_RIGHT_PARENTHESIS,   // )
    TOKEN_EOF
} TokenType;

// Stores a token, text is only really needed for TOKEN_IDENTIFIER
typedef struct Token {
    TokenType type;
    char* text;
    void* info;
    struct Token* next;
    int addr;
} Token;

// Used to store a program's information. Used primarly for token functions to store state
typedef struct {
    char* text;
    int next_token_start;
    Token* next_token;
    bool at_end;
} Program;

Token* BecolMallocToken();
void   BecolFreeToken(Token* token);

Program* BecolGetProgram(char* prog);
void     BecolFreeProgram(Program* prog);

Token* BecolNextToken(Program* prog);
Token* BecolPeekToken(Program* prog);

#endif
