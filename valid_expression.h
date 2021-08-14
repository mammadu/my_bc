#ifndef valid_expression_H
#define valid_expression_H

#include "lexer.h"
#include "my_c_functions.h"

int valid_expression(tokens* tokens);
int invalid_characters(tokens* tokens); //check the number token to make sure only digits 0-9 are in the string
int consecutive_operators(tokens* token); //checks if there are multiple operators consecutively
int invalid_parentheses(tokens* token);
int spaces_between_numbers(tokens* token);
int non_val_after_open_par(tokens* token);
int non_val_before_close_par(tokens* token);
int is_operator(char* token_type);
int is_par(char* token_type);

#endif