#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
/*#include "../lib/my_debug.h"*/

typedef union TokenValue TokenValue;
union TokenValue {
    // value
    int ival;
    char cval;
    float fval;
    double dval;
    bool bval;
};

typedef enum TokenType {
    TT_CHAR = 0,
    TT_INT,
    TT_DOUBLE,
    TT_FLOAT,
    TT_EOF,
    TT_BOOL,

    // Arithmetic operators
    TT_PLUS,
    TT_MULT,
    TT_MINUS,
    TT_DIV,
    TT_MODULO,
    
    TT_COUNT
} TokenType;

typedef struct token_t token_t;
struct token_t {
    TokenType type;
    TokenValue value;
};

#define token_free(tokenptr) free(token);
token_t * new_token(TokenType type, TokenValue *pval);
void token_print(token_t *token);


#endif // TOKEN_H
