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
        .current_token = NULL,
    };
    return lexer;
}

#define isoperator(chr) ((chr == '+' || chr == '-' || chr == '/' || chr == '%' || chr == '*') ? true : false)      

//TODO: lexer_get_multi_digit... for all token type

token_t * lexer_get_multi_digit_integer_token(lexer_t *lexer)
{
    char *buffer = lexer->content;
    int cursor = lexer->cursor;

    char int_buff[MAXINT] = {0};
    int pos = 0;
    int_buff[0] = buffer[cursor];
    
    while (!isspace(buffer[cursor]) && 
           !isoperator(buffer[cursor]) && buffer[cursor] != '\0') 
    {
        int_buff[pos++] = buffer[cursor++];
    }

    lexer->cursor = cursor;

    TokenValue val = {
        .ival = atoi(int_buff)
    };
    return new_token(TT_INT, &val);

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

    while (current_char != '\0') 
    {
        if (isspace(current_char)) {

            lexer->cursor++;

        } else if (isdigit(current_char)) {

            return lexer_get_multi_digit_integer_token(lexer);

        } else if (current_char == '+') {

            lexer->cursor++;
            return new_token(TT_PLUS, NULL);

        } else if (current_char == '-'){

            lexer->cursor++;
            return new_token(TT_MINUS, NULL);

        } else if (current_char == '/') {

            lexer->cursor++;
            return new_token(TT_DIV, NULL);

        } else if (current_char == '%') {

            lexer->cursor++;
            return new_token(TT_MODULO, NULL);

        } else if (current_char == '*') {

            lexer->cursor++;
            return new_token(TT_MULT, NULL);

        } else {
            fprintf(stderr, DBG"%s: unknown character read\n", __func__);
            exit(1);
        }

        current_char = lexer->content[lexer->cursor];
    }


    return new_token(TT_EOF, NULL); 
}



token_t lexer_evaluate_expression(lexer_t *lexer)
{
    assert(lexer);

    // This function returns a token only after either left token is
    // occupied or if all the three i.e left right and op are occupied

    token_t result = {0};
    token_t *op = NULL;
    token_t *left = NULL;
    token_t *right = NULL;

    lexer->current_token = lexer_get_next_token(lexer);
    while (lexer->current_token->type != TT_EOF) {

        if (left == NULL) {

            if (token_is_operator(lexer->current_token)) 
                lexer_panic("Invalid Syntax\n");

            left = lexer->current_token;
            token_print(left);

        } else if (op == NULL ) {
            
            if (!token_is_operator(lexer->current_token)) 
                lexer_panic("Invalid Syntax\n");

            op = lexer->current_token;
            token_print(op);

        } else if (right == NULL) {

            if (token_is_operator(lexer->current_token)) 
                lexer_panic("Invalid Syntax\n");

            right = lexer->current_token;
            token_print(right);

        } else {
            result = token_calculate(left, right, op);
            *left = result;
            op = NULL;
            right = NULL;
            token_print(left);
            continue;
        }
        lexer->current_token = lexer_get_next_token(lexer);
    }

    //TODO: better error handling
    if (left != NULL && right != NULL && op != NULL) {
        result = token_calculate(left, right, op);
    } else if (left != NULL && op != NULL && right == NULL) {
        lexer_panic("Invalid Syntax\n");
    } else result = *left; 
    
    return result;
}

