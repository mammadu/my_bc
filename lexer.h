#ifndef lexer_H
#define lexer_H

#include "my_c_functions.h"

typedef struct tokens_holder {
    char** tokens;      //tokens[0][1] = '+'
    char** token_type;  //token_type[0][1] = "Operator"
    int token_count;
} tokens;

int tokens_counter(char* source);



#endif