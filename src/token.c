#include "token.h"
#include <assert.h>

// creates a token 
token_t * new_token(TokenType type, TokenValue *pval)
{
    token_t *token = (token_t *)calloc(0, sizeof(token_t));
    if (token == NULL) {
        fprintf(stderr, ERROR"%s: token is null\n", __func__);
        exit(1);
    }

    token->type = type;
    TokenValue value = {0}; 
    switch(type)
    {
        case TT_CHAR:
            value = *pval; 
            token->value.cval = value.cval;
            break;
        case TT_INT:
            value = *pval; 
            token->value.ival = value.ival;
            break;
        case TT_DOUBLE:
            value = *pval; 
            token->value.dval = value.dval;
            break;
        case TT_FLOAT:
            value = *pval; 
            token->value.fval = value.fval;
            break;
        case TT_BOOL:
            value = *pval; 
            token->value.bval = value.bval;
            break;
        case TT_EOF:
        case TT_PLUS:
        case TT_MULT:
        case TT_MINUS:
        case TT_DIV:
        case TT_MODULO:
            break;
        default:
            fprintf(stderr, ERROR"%s: new kind\n", __func__);
            exit(1);
            break;
    }
    return token;
}


//prints a token
void token_print(token_t *token)
{
    switch(token->type) {
        case TT_INT:
            printf("TOKEN(TT_INT, %i)\n", token->value.ival);
            break;
        case TT_CHAR:
            printf("TOKEN(TT_CHAR, %c)\n", token->value.cval);
            break;
        case TT_DOUBLE:
            printf("TOKEN(TT_DOUBLE, %f)\n", token->value.dval);
            break;
        case TT_FLOAT:
            printf("TOKEN(TT_FLOAT, %f)\n", token->value.fval);
            break;
        case TT_BOOL:
            printf("TOKEN(TT_BOOL, %s)\n",
                    (int)token->value.bval == 0 ? "false" : "true");
            break;
        case TT_EOF:
            printf("TOKEN(TT_EOF)\n");
            break;
        case TT_PLUS:
            printf("TOKEN(TT_PLUS)\n");
            break;
        case TT_MULT:
            printf("TOKEN(TT_MULT)\n");
            break;
        case TT_MINUS:
            printf("TOKEN(TT_MINUS)\n");
            break;
        case TT_DIV:
            printf("TOKEN(TT_DIV)\n");
            break;
        case TT_MODULO:
            printf("TOKEN(TT_MODULO)\n");
            break;
        default:
            fprintf(stderr, DBG"%s: unkown type\n", __func__);
            break;
    }
}

token_t token_calculate(token_t *left, token_t *right, token_t *op)
{
    if (left == NULL || right == NULL || op == NULL) {
        fprintf(stderr, DBG"%s: null arguments\n", __func__);
        exit(1);
    }
    token_t result = {0};
    switch(op->type)
    {
        case TT_PLUS:
            result.value.ival = left->value.ival + right->value.ival;
            break;
        case TT_MINUS:
            result.value.ival = left->value.ival - right->value.ival;
            break;
        case TT_MODULO:
            result.value.ival = left->value.ival % right->value.ival;
            break;
        case TT_MULT:
            result.value.ival = left->value.ival * right->value.ival;
            break;
        case TT_DIV:
            result.value.ival = left->value.ival / right->value.ival;
            break;
        default:
            fprintf(stderr, DBG"%s: operator not accounted\n", __func__);
            break;
    }
    result.type = left->type;
    return result;
}


bool token_set_value(token_t *token, TokenValue value)
{
    switch(token->type)
    {
        case TT_CHAR:
            token->value.cval = value.cval;
            break;
        case TT_BOOL:
            token->value.bval = value.bval;
            break;
        case TT_INT:
            token->value.ival = value.ival;
            break;
        case TT_DOUBLE:
            token->value.dval = value.dval;
            break;
        case TT_FLOAT:
            token->value.fval = value.fval;
            break;
        default:
            fprintf(stderr, DBG"%s: token type not accounted for\n", __func__);
            exit(1);
            break;
    }
    return true;
}

bool token_is_operator(token_t *token)
{
    return (
            token->type == TT_PLUS || 
            token->type == TT_MINUS || 
            token->type == TT_DIV || 
            token->type == TT_MODULO || 
            token->type == TT_MULT
            ) ? true : false;
}
