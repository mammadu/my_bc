#ifndef shunting_yard_H
#define shunting_yard_H

#include "my_c_functions.h"
#include "lexer.h"

typedef struct shunting_yard {
    //malloc output_queue as same size as token_size.
    //push index of values and proper operators to output queue
    //last character is null
    char** output_queue; // "a b + c d e + * *"
    char** operator_stack;
    int** operator_stack_priority;
    int output_queue_count;
    int operator_stack_count;
    
    //use output_queue and operator_stack to create RPN
} shunting_yard;

shunting_yard* push_operator_to_stack(shunting_yard* syd, tokens* tokens, int index);

shunting_yard* my_rpn(tokens* tokens);

shunting_yard* syd_mem_alloc(shunting_yard* syd, tokens* tokens);

#endif