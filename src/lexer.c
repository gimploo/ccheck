#include "lexer.h"

lexer_t lexer_init(char *content, int content_size)
{
    assert(content);
    assert(content_size > 0);
    lexer_t lexer = {
        .content = content,
        .content_size = content_size,
        .cursor = 0,
        .stop = false, 
        .current_token = NULL
    };
    return lexer;
}

token_t * lexer_get_next_token(lexer_t *lexer)
{
    assert(lexer);
    /*
     * lexer->cursor is zero indexed 
     * and lexer->content_size includes null terminator
     */
    if (lexer->cursor >= (lexer->content_size-1)) return new_token(TT_EOF, NULL);

    char current_char = lexer->content[lexer->cursor];

    TokenValue tk_val = {0};

    while (current_char != '\0') 
    {
        if (isspace(current_char)) {
            lexer->cursor++;
        } else if (isdigit(current_char)) {
            lexer->cursor++;
            tk_val.ival = current_char - '0';
            return new_token(TT_INT, &tk_val);
        } else if (current_char == '+') {
            lexer->cursor++;
            return new_token(TT_PLUS, NULL);
        } else if (current_char == '-'){
            lexer->cursor++;
            return new_token(TT_MINUS, NULL);
        } else {
            fprintf(stderr, ERROR"%s: unknown character read\n", __func__);
        }

        current_char = lexer->content[lexer->cursor++];
    }


    return new_token(TT_EOF, NULL); 
}


int lexer_evaluate_expression(lexer_t *lexer)
{
    assert(lexer);
    lexer->current_token = lexer_get_next_token(lexer);
    token_print(lexer->current_token);
    token_t *left = lexer->current_token;

    lexer->current_token = lexer_get_next_token(lexer);
    token_t *op = lexer->current_token;
    token_print(lexer->current_token);

    lexer->current_token = lexer_get_next_token(lexer);
    token_t *right = lexer->current_token;
    token_print(lexer->current_token);

    token_print(lexer_get_next_token(lexer));
    
    int total;
    switch(op->type)
    {
        case TT_PLUS:
            total = left->value.ival + right->value.ival;
            break;
        case TT_MINUS:
            total = left->value.ival - right->value.ival;
            break;
        default:
            fprintf(stderr, ERROR"%s: operator not accounted\n", __func__);
            break;
    }
    return total;  
}

