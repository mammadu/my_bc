#include "shunting_yard.h"

//main function returns a rpn of the tokenized input
shunting_yard* my_rpn(tokens* tokens)
{
    shunting_yard* syd = malloc(sizeof(shunting_yard));

    for(int i = 0; i < tokens->token_count; i ++)
    {
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR]))
        { 
            syd->output_queue = my_strdup(tokens->tokens[i]);
            syd->output_queue_count += 1;
        }
        
    }
}