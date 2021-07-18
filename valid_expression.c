#include "valid_expression.h"

/*
runs through a series of functions to ensure expression is valid.
Returns 0 on success, any other number on failure
*/
int valid_expression(tokens* tokens) 
{
    int error_val = 0;
    error_val = error_val + invalid_characters(tokens);
    return error_val;
}

int invalid_characters(tokens* tokens) //check the number token to make sure only digits 0-9 are in the string
{
    for (int i = 0; i < tokens->token_count; i++) //loop to go through every token
    {
        if (my_strcmp(tokens->token_type[i], VAL) == SAME) //check if the token is a number
        {
            for (int j = 0; j < my_strlen(tokens->tokens[i]); j++) //go through token string to check for any outlawed characters
            {
                if (tokens->tokens[i][j] < '0' || tokens->tokens[i][j] > '9')
                {
                    return 0;
                }
            }
        }
    }
    return 1; //otherwise return 1 meaning the string has invalid characters
}

int is_add(char* token_type)
{
    if(my_strcmp(token_type[i], ADD) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_sub(char* token_type)
{
    if(my_strcmp(token_type[i], SUB) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_mult(char* token_type)
{
    if(my_strcmp(token_type[i], MULT) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_div(char* token_type)
{
    if(my_strcmp(token_type[i], DIV) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_mod(char* token_type)
{
    if(my_strcmp(token_type[i], MOD) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_operand(char* token_type)
{
    if (is_add(token_type) || is_sub(token_type) || is_mult(token_type) || is_div(token_type) || is_mod(token_type))
    {
        return 1;
    }
    retun 0;
}


int no_consecutive_operators(tokens* token)
{
     for (int i = 0; i < tokens->token_count - 1; i++) //loop to go through every token
    {
        // if (is_operand(tokens->token_type[i]) && is_operand(tokens->token_type[i])) //check if the token is an operand
        // {
        //     return 1;
        // }
    }
}

//main for testing
int main (int argc, char** argv)
{
    tokens* tokens = malloc(sizeof(tokens));
    tokens->token_count = argc - 1;
    tokens->tokens = malloc(tokens->token_count * sizeof(char*));
    tokens->token_type = malloc(tokens->token_count * sizeof(char*));

    for (int i = 0; i < tokens->token_count; i++)
    {
        tokens->tokens[i] = my_strdup(argv[i + 1]);
        tokens->token_type[i] = my_strdup(VAL);
    }

    int error_val = valid_expression(tokens);
    printf("error_val = %d\n", error_val);
    return 0;
}