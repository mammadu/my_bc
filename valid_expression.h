#ifndef valid_expression_H
#define valid_expression_H

#include "lexer.h"
#include "my_c_functions.h"

#define ADD "ADD"
#define SUB "SUB"
#define MULT "MULT"
#define DIV "DIV"
#define MOD "MOD"
#define NEG "NEG" //when '-' is in front of a number token
#define VAL "VAL"
#define SPACE "SPACE"
#define OPEN_PAR "OPEN_PAR"
#define CLOSE_PAR "CLOSE_PAR"

int valid_expression(tokens* tokens);
int invalid_characters(tokens* tokens); //check the number token to make sure only digits 0-9 are in the string
int consecutive_operators(tokens* token); //checks if there are multiple operators consecutively


#endif