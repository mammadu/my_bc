#ifndef lexer_H
#define lexer_H

#include "my_c_functions.h"
//#include "valid_expression.h"

#define SYNTAX_ERROR -1
#define FIRST_CHAR 0

typedef struct tokens_holder {
    char** tokens;      //tokens[0][1] = '+'
    char** token_type;  //token_type[0][1] = "Operator"
    int token_count;
} tokens;

int tokens_counter(char* source);

char** token_extractor(char* source, int token_count);

void token_strings_initializer(char** src ,int strings_count , int len);

char** token_type_extractor(char** tokens, int token_count, char* source);



#endif