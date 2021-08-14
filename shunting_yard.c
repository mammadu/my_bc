#include "shunting_yard.h"

 shunting_yard* syd_mem_alloc(shunting_yard* syd, tokens* tokens)
 {
    syd->output_queue = malloc(sizeof(char*) * tokens->token_count); 
    syd->operator_stack = malloc(sizeof(char*) * tokens->token_count);
    syd->operator_stack_priority = malloc(sizeof(int) * tokens->token_count);
    syd->output_queue_count = 0;
    syd->operator_stack_count = 0;

    return syd;
 }

void pop_stack(shunting_yard* syd)
{
    int operator_stack_index = syd->operator_stack_count - 1;
    free(syd->operator_stack[operator_stack_index]);
    // free(syd->operator_stack_priority[operator_stack_index]);
    syd->operator_stack_count -= 1;
}

void push_to_queue(shunting_yard* syd, char* item)
{
    syd->output_queue[syd->output_queue_count] = my_strdup(item);
    syd->output_queue_count += 1;
}

void pop_stack_to_queue(shunting_yard* syd)
{
    int operator_stack_index = syd->operator_stack_count - 1;
    push_to_queue(syd, syd->operator_stack[operator_stack_index]);
    pop_stack(syd);
}

shunting_yard* push_operator_to_stack(shunting_yard* syd, tokens* tokens, int index) // does this create a new syd in memory?
{
    syd->operator_stack_priority[syd->operator_stack_count] =  tokens->token_priority[index];
    syd->operator_stack[syd->operator_stack_count] = my_strdup(tokens->tokens[index]);
    syd->operator_stack_count += 1;
    return syd;
}

void print_output_queue(shunting_yard* syd)//for debugging
{
    printf("output_queue: ");
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        printf("%s", syd->output_queue[i]);
    }
    printf("\n");
}

void print_operator_stack(shunting_yard* syd) //for debugging
{
    printf("operator_stack: ");
    for (int i = 0; i < syd->operator_stack_count; i++)
    {
        printf("%s", syd->operator_stack[i]);
    }
    printf("\n");
}

//main function returns a rpn of the tokenized input
shunting_yard* my_rpn(tokens* tokens)
{
    shunting_yard* syd = malloc(sizeof(shunting_yard));
    syd = syd_mem_alloc(syd, tokens);    

    for(int i = 0; i < tokens->token_count; i++)
    {
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR])) 
        {
            push_to_queue(syd, tokens->tokens[i]); //This line should do the same thing as the next two commented lines
            // syd->output_queue[syd->output_queue_count] = my_strdup(tokens->tokens[i]);
            // syd->output_queue_count += 1;
        }

        else if (tokens->token_priority[i] > PRIORITY_ONE && tokens->token_priority[i] < PRIORITY_FOUR) //Operator entry 
        {
            if(syd->operator_stack_count > 0 && (tokens->token_priority[i] > syd->operator_stack_priority[syd->operator_stack_count - 1]))
            {
                printf("first if\n");
                syd = push_operator_to_stack(syd, tokens, i);
                //push operator, push priority, and increment syd->operator_stack_count + 1
            }

            else if (syd->operator_stack_count > 0 && tokens->token_priority[i] <= syd->operator_stack_priority[syd->operator_stack_count - 1])
            {
                printf("second if\n");
                pop_stack_to_queue(syd);
                syd = push_operator_to_stack(syd, tokens, i);
                //pop operator, pop priority
                //push token[token][i]
            }

            else if(syd->operator_stack_count == 0)
            {

                printf("first if\n");
                syd = push_operator_to_stack(syd, tokens, i);
                //push operator
            }
        }

        else if (tokens->token_priority[i] == PRIORITY_ONE)
        {
            syd = push_operator_to_stack(syd, tokens, i);
        }
        else if (tokens->token_priority[i] == PRIORITY_FOUR) //dealing with closing parentheses
        {
            while (syd->operator_stack_count > 0 && syd->operator_stack_priority[syd->operator_stack_count - 1] != PRIORITY_ONE)
            {
                pop_stack_to_queue(syd);
            }
            pop_stack(syd);
        }

        print_output_queue(syd);
        print_operator_stack(syd);
        printf("\n");

    }
    for (int i = syd->operator_stack_count; i > 0; i--)
    {
        pop_stack_to_queue(syd);
    }
    return syd;
}

void free_shunting_yard(shunting_yard* syd)
{
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        free(syd->output_queue[i]);
    }
    free(syd->output_queue);

    for (int i = 0; i < syd->operator_stack_count; i++)
    {
        free(syd->operator_stack[i]);
    }
    free(syd->operator_stack);
    free(syd->operator_stack_priority);
    free(syd);
}

