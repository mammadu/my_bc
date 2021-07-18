#ifndef valid_expression_H
#define valid_expression_H

#include "lexer.h"
#include "my_c_functions.h"

#define ADD "ADD"
#define SUB "SUB"
#define MULT "MULT"
#define DIV "DIV"
#define MOD "MOD"
#define VAL "NUMBERS"
#define SPACE "SPACE"
#define OPEN_PAR "OPEN_PAR"
#define CLOSE_PAR "CLOSE_PAR"

int valid_expression(tokens* tokens);
int valid_characters(tokens* tokens);


#endif