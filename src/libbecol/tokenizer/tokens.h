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
    TOKEN_LEFT_CURLY_BRACKET,
    TOKEN_RIGHT_CURLY_BRACKET,
    TOKEN_IDENTIFIER
} TokenType;

// Stores a token, text is only really needed for TOKEN_IDENTIFIER
typedef struct Token {
    TokenType type;
    char* text;
    struct Token* next;
    int addr;
} Token;

// Used to store a program's information. Used primarly for token functions to store state
typedef struct {
    char* text;
    int next_token_start;
    Token* next_token;
} Program;

Token* BecolMallocToken(int text_len);
void   BecolFreeToken(Token* token);

Program* BecolGetProgram(char* prog);
void     BecolFreeProgram(Program* prog);

Token* BecolNextToken(Program* prog);
Token* BecolPeekToken(Program* prog);

#endif
