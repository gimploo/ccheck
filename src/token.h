#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
/*#include "../lib/my_debug.h"*/

#define MAXINT      (sizeof(int))
#define MAXFLOAT    (sizeof(float))
#define MAXDOUBLE   (sizeof(double))

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

static inline bool token_is_integer(token_t *token) { return (token->type == TT_INT) ? true : false; }
static inline bool token_is_float(token_t *token) { return (token->type == TT_FLOAT) ? true : false; }
static inline bool token_is_double(token_t *token) { return (token->type == TT_DOUBLE) ? true : false; }

#define token_free(tokenptr) (free(token))
token_t *   new_token(TokenType type, TokenValue *pval);
void        token_print(token_t *token);
token_t     token_calculate(token_t *left, token_t *right, token_t *op);
bool        token_set_value(token_t *token, TokenValue value);
bool        token_add_token_of_same_type(token_t *, token_t *);
bool        token_is_operator(token_t *token);


#endif // TOKEN_H
