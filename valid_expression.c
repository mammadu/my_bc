#include "valid_expression.h"

/*
runs through a series of functions to ensure expression is valid.
Returns 0 on success, any other number on failure
*/
int valid_expression(tokens* tokens) 
{
    int error_val = 0;
    error_val = error_val + valid_characters(tokens);
    return error_val;
}

int valid_characters(tokens* tokens) //check the number token to make sure only digits 0-9 are in the string
{
    for (int i = 0; i < tokens->token_count; i++) //loop to go through every token
    {
        if (my_strcmp(tokens->token_type[i], VAL) == SAME) //check if the token is a number
        {
            for (int j = 0; j < my_strlen(tokens->tokens[i]); j++) //go through token string to check for any outlawed characters
            {
                if (tokens->tokens[i][j] < '0' || tokens->tokens[i][j] > '9')
                {
                    return -1;
                }
            }
        }
    }
    return 0; //otherwise return 0 for success
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