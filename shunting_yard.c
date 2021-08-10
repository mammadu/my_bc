#include "shunting_yard.h"

 shunting_yard* syd_mem_alloc(shunting_yard* syd)
 {
    syd->output_queue = malloc(sizeof(char*) * tokens->token_count); 
    syd->operator_stack = malloc(sizeof(char*) * tokens->token_count);
    syd->output_queue_count = 0;
    syd->operator_stack_count = 0;
 }

//main function returns a rpn of the tokenized input
shunting_yard* my_rpn(tokens* tokens)
{
    shunting_yard* syd = malloc(sizeof(shunting_yard));
    syd = syd_mem_alloc(syd);

    for(int i = 0; i < tokens->token_count; i ++)
    {
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR])) { 
            syd->output_queue[syd->output_queue_count] = my_strdup(tokens->tokens[i]);
            syd->output_queue_count += 1;
        } else if (tokens->token_priority[i][FIRST_CHAR] > 1 && tokens->token_priority[i][FIRST_CHAR] < 4) {
            
        }
        
    }
}
