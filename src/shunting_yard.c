#include "../include/shunting_yard.h"

shunting_yard *syd_mem_alloc(shunting_yard *syd, tokens *tokens)
{
    syd->output_queue = malloc(sizeof(char *) * tokens->token_count);
    syd->operator_stack = malloc(sizeof(char *) * tokens->token_count);
    syd->operator_stack_priority = malloc(sizeof(int) * tokens->token_count);
    syd->output_queue_count = 0;
    syd->operator_stack_count = 0;

    return syd;
}

void pop_stack(shunting_yard *syd)
{
    int operator_stack_index = syd->operator_stack_count - 1;
    free(syd->operator_stack[operator_stack_index]);
    // free(syd->operator_stack_priority[operator_stack_index]);
    syd->operator_stack_count -= 1;
}

void push_to_queue(shunting_yard *syd, char *item)
{
    syd->output_queue[syd->output_queue_count] = my_strdup(item);
    syd->output_queue_count += 1;
}

void pop_stack_to_queue(shunting_yard *syd)
{
    int operator_stack_index = syd->operator_stack_count - 1;
    push_to_queue(syd, syd->operator_stack[operator_stack_index]);
    pop_stack(syd);
}

shunting_yard *push_operator_to_stack(shunting_yard *syd, tokens *tokens, int index) // does this create a new syd in memory?
{
    syd->operator_stack_priority[syd->operator_stack_count] = tokens->token_priority[index];
    syd->operator_stack[syd->operator_stack_count] = my_strdup(tokens->tokens[index]);
    syd->operator_stack_count += 1;
    return syd;
}

void print_output_queue(shunting_yard *syd) //for debugging
{
    printf("output_queue: ");
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        printf("%s", syd->output_queue[i]);
    }
    printf("\n");
}

void print_operator_stack(shunting_yard *syd) //for debugging
{
    printf("operator_stack: ");
    for (int i = 0; i < syd->operator_stack_count; i++)
    {
        printf("%s", syd->operator_stack[i]);
    }
    printf("\n");
}

void operator_router(shunting_yard *syd, tokens *tokens, int token_index)
{
    if (syd->operator_stack_count > 0 && (tokens->token_priority[token_index] > syd->operator_stack_priority[syd->operator_stack_count - 1])) //if new operator has higher priority last operator on stack, add new operator to stack
    {
        syd = push_operator_to_stack(syd, tokens, token_index);
        //push operator, push priority, and increment syd->operator_stack_count + 1
    }

    else if (syd->operator_stack_count > 0 && tokens->token_priority[token_index] <= syd->operator_stack_priority[syd->operator_stack_count - 1]) //else, pop top of operator stack to queue, push new operator to stack
    {
        pop_stack_to_queue(syd);
        syd = push_operator_to_stack(syd, tokens, token_index);
        //pop operator, pop priority
        //push token[token][i]
    }

    else if (syd->operator_stack_count == 0) //if stack is empty, push to stack
    {
        syd = push_operator_to_stack(syd, tokens, token_index);
    }
}

void parentheses_router(shunting_yard *syd, tokens *tokens, int token_index)
{
    if (tokens->token_priority[token_index] == PRIORITY_ONE) //always push '(' to stack
    {
        syd = push_operator_to_stack(syd, tokens, token_index);
    }
    else if (tokens->token_priority[token_index] == PRIORITY_FOUR) //when given ')', pop all operators to queue up until '('
    {
        while (syd->operator_stack_count > 0 && syd->operator_stack_priority[syd->operator_stack_count - 1] != PRIORITY_ONE)
        {
            pop_stack_to_queue(syd);
        }
        pop_stack(syd); //pop  matching '('
    }
}

void token_router(shunting_yard *syd, tokens *tokens) //Pushes tokens to output_queue or operator stack
{
    for (int i = 0; i < tokens->token_count; i++)
    {
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR])) //push numbers to output queue
        {
            push_to_queue(syd, tokens->tokens[i]);
        }

        else if (is_operator(tokens->token_type[i])) //routes operators to operator stack
        {
            operator_router(syd, tokens, i);
        }

        else if (is_par(tokens->token_type[i])) //routes parentheses to stack or frees matching parentheses.
        {
            parentheses_router(syd, tokens, i);
        }
    }
}

//main function returns a rpn of the tokenized input
shunting_yard *my_rpn(tokens *tokens)
{
    shunting_yard *syd = malloc(sizeof(shunting_yard)); //allocate memory for syd
    syd = syd_mem_alloc(syd, tokens);                   //initialize syd struct

    token_router(syd, tokens); //Pushes tokens to output_queue or operator stack

    for (int i = syd->operator_stack_count; i > 0; i--) //pop last items of operator stack to queue
    {
        pop_stack_to_queue(syd);
    }
    return syd;
}

void free_shunting_yard(shunting_yard *syd)
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
