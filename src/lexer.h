#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef struct lexer_t lexer_t;
struct lexer_t {
    char *content;
    int content_size;
    int cursor; // keeps track of last stdin char entry before null char
    bool stop;

    token_t *current_token;
};

static inline size_t lexer_inc_content_size(lexer_t *program)
{
    program->cursor = program->content_size;
    program->content_size++;
    return (program->cursor);
}

lexer_t lexer_init(char *content, int content_size);
token_t * lexer_get_next_token(lexer_t *lexer);
int lexer_evaluate_expression(lexer_t *lexer);

#endif //LEXER_H

