#ifndef lexer_H
#define lexer_H

#include "my_c_functions.h"

#define ADD "ADD"
#define SUB "SUB"
#define MULT "MULT"
#define DIV "DIV"
#define MOD "MOD"
#define VAL "VAL"
#define SPACE "SPACE"
#define OPEN_PAR "OPEN_PAR"
#define CLOSE_PAR "CLOSE_PAR"
#define UNKNOWN "UNKNOWN"

#define SYNTAX_ERROR -1
#define FIRST_CHAR 0

typedef struct tokens_holder {
    char** tokens;      //tokens[0][1] = '+'
    char** token_type;  //token_type[0][1] = "Operator"
    int token_count;
} tokens;

void token_strings_initializer(char** src ,int strings_count , int len);

int tokens_counter(char* source);

int number_extractor( char* source, char* dst, int index);

char** token_extractor(char* source, int token_count);

char** token_type_extractor(char** tokens, int token_count, char* source);

tokens* tokenizer(char* source);


#endif