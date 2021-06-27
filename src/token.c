#didfinclude "token.h"
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
            fprintf(stderr, ERROR"%s: unkown type\n", __func__);
            break;
    }
}
