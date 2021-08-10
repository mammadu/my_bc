#ifndef shunting_yard_H
#define shunting_yard_H

#include "my_c_functions.h"
#include "lexer.h"

typedef struct shunting_yard {
    //malloc output_queue as same size as token_size.
    //push index of values and proper operators to output queue
    //last character is null
    char** output_queue;
    char** operator_stack;
    int output_queue_count;

    //use output_queue and operator_stack to create RPN
} shunting_yard;


#endif