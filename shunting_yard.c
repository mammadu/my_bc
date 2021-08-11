#include "shunting_yard.h"

 shunting_yard* syd_mem_alloc(shunting_yard* syd, tokens* tokens)
 {
    syd->output_queue = malloc(sizeof(char*) * tokens->token_count); 
    syd->operator_stack = malloc(sizeof(char*) * tokens->token_count);
    syd->operator_stack_priority = malloc(sizeof(int*) * tokens->token_count);
    syd->output_queue_count = 0;
    syd->operator_stack_count = 0;

    return syd;
 }

void pop_stack(shunting_yard* syd)
{
    operator_stack_index = operator_stack_count - 1;
    free(syd->operator_stack[operator_stack_index]);
    free(syd->operator_stack_priority[operator_stack_index]);
    syd->operator_stack_count -= 1;
}

void pop_stack_to_queue(shunting_yard* syd)
{
    operator_stack_index = operator_stack_count - 1;
    syd->output_queue[output_queue_count] = my_strdup(syd->operator_stack[operator_stack_index]);
    syd->output_queue_count += 1;
    pop_stack(shunting_yard* syd);
}

shunting_yard* push_operator_to_stack(shunting_yard* syd, tokens* tokens, int index)
{
    syd->operator_stack_priority[syd->operator_stack_count] =  tokens->token_priority[index];
    syd->operator_stack[syd->operator_stack_count] = my_strdup(tokens->tokens[index]);
    return syd;
}

//main function returns a rpn of the tokenized input
shunting_yard* my_rpn(tokens* tokens)
{
    shunting_yard* syd = malloc(sizeof(shunting_yard));
    syd = syd_mem_alloc(syd, tokens);

    for(int i = 0; i < tokens->token_count; i ++)
    {
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR])) 
        { 
            syd->output_queue[syd->output_queue_count] = my_strdup(tokens->tokens[i]);
            syd->output_queue_count += 1;
        } 

        else if (tokens->token_priority[i][FIRST_CHAR] > 1 && tokens->token_priority[i][FIRST_CHAR] < 4) //Operator entry 
        {
            if(syd->operator_stack_count > 0 && tokens->token_priority[i] > syd->operator_stack_priority[syd->operator_stack_count - 1])
            {
                //push operator, push priority, and increment syd->operator_stack_count + 1
            } else if (syd->operator_stack_count > 0 && tokens->token_priority[i] <= syd->operator_stack_priority[syd->operator_stack_count - 1])
            {
                //pop operator, pop priority
                //push token[token][i]           
            }else if(syd->operator_stack_count == 0)
            {
                //push operator
            }
        }
        else if (tokens->token_priority[i][FIRST_CHAR] == PRIORITY_FOUR) //dealing with closing parentheses
        {
            while (syd->operator_stack_count > 0 && my_strcmp(syd->operator_stack[syd->operator_stack_count - 1],"(") != 0)
            {
                pop_stack_to_queue(syd);
            }
            pop_stack(syd);
        }
    }
}
