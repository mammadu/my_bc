#include "valid_expression.h"

/*
runs through a series of functions to ensure expression is valid.
Returns 0 on success, any other number on failure
*/
int valid_expression(tokens* tokens) 
{
    int error_val = 0;
    error_val = error_val + invalid_characters(tokens);
    error_val = error_val + consecutive_operators(tokens);
    error_val = error_val + invalid_parentheses(tokens);
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
                else
                {
                    return 1;
                }                
            }
        }
    }
    return 0; //otherwise return 1 meaning the string has invalid characters
}

int is_add(char* token_type)
{
    if(my_strcmp(token_type, ADD) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_sub(char* token_type)
{
    if(my_strcmp(token_type, SUB) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_mult(char* token_type)
{
    if(my_strcmp(token_type, MULT) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_div(char* token_type)
{
    if(my_strcmp(token_type, DIV) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_mod(char* token_type)
{
    if(my_strcmp(token_type, MOD) == SAME)
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
    return 0;
}

int is_val(char* token_type)
{
    if(my_strcmp(token_type, VAL) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_open_par(char* token_type)
{
    if(my_strcmp(token_type, OPEN_PAR) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_close_par(char* token_type)
{
    if(my_strcmp(token_type, CLOSE_PAR) == SAME)
    {
        return 1;
    }
    return 0;
}

int is_par(char* token_type)
{
    if(is_open_par(token_type) || is_close_par(token_type))
    {
        return 1;
    }
    return 0;
}

int is_space(char* token_type)
{
    if(my_strcmp(token_type, SPACE) == SAME)
    {
        return 1;
    }
    return 0;
}

int consecutive_operators(tokens* token) //checks if there are multiple operators consecutively
{
    for (int i = 0; i < token->token_count - 1; i++) //loop to go through every token
    {
        if (is_operand(token->token_type[i])) //check if the token is an operand
        {
            for(int j = i + 1; j < token->token_count; j++) //loop to check next token
            {
                if(is_space(token->token_type[j])) //if the token is a space, skip to the next one
                {
                    continue;
                }
                else if (is_sub(token->token_type[j])) //'-' after another operand is ok
                {
                    break;
                }
                else if (is_operand(token->token_type[j])) //consecutive operands is not ok, return 1
                {
                    return 1;
                }
            }
        }
    }
    return 0; //if the outer loop completes, there are no unallowed consecutive operands
}

int invalid_parentheses(tokens* token)
{
    int parentheses_stack = 0;
    for (int i = 0; i < token->token_count; i++)
    {
        if (is_open_par(token->token_type[i])) //if '(', add 1 to stack
        {
            parentheses_stack += 1;
        }
        else if (is_close_par(token->token_type[i])) //if ')', subtract 1 from stack
        {
            parentheses_stack -= 1;
        }
        /*
        //if stack is ever negative, 
        that means there are more close brackets then open brackets, 
        therefore there is a syntax error
        */
        if (parentheses_stack < 0) 
        {
            return 1;
        }
    }
    //if stack is not 0, the counts of '(' and ')' are not equal, therefore there is a syntax error
    if (parentheses_stack != 0)
    {
        return 1;
    }
    return 0;
}

//main for testing invalid_characters()
// int main (int argc, char** argv)
// {
//     tokens* tokens = malloc(sizeof(tokens));
//     tokens->token_count = argc - 1;
//     tokens->tokens = malloc(tokens->token_count * sizeof(char*));
//     tokens->token_type = malloc(tokens->token_count * sizeof(char*));

//     for (int i = 0; i < tokens->token_count; i++)
//     {
//         tokens->tokens[i] = my_strdup(argv[i + 1]);
//         tokens->token_type[i] = my_strdup(VAL);
//     }

//     int error_val = valid_expression(tokens);
//     printf("error_val = %d\n", error_val);
//     return 0;
// }

//main for testing consecutive_operators()
int main()
{
    tokens* tokens = malloc(sizeof(tokens));

    int str_count = 4;
    
    char* str[str_count];
    int i = 0;    
    str[i] = ")";
    i++;
    str[i++] = "(";
    i++;
    str[i++] = ")";
    i++;
    str[i++] = ")";

    char* types[str_count];
    i = 0;
    types[i] = CLOSE_PAR;
    i++;
    types[i] = OPEN_PAR;
    i++;
    types[i] = CLOSE_PAR;
    i++;
    types[i] = OPEN_PAR;

    tokens->token_count = str_count;
    tokens->tokens = malloc(tokens->token_count * sizeof(char*));
    tokens->token_type = malloc(tokens->token_count * sizeof(char*));

    for (int i = 0; i < tokens->token_count; i++)
    {
        tokens->tokens[i] = my_strdup(str[i]);
        tokens->token_type[i] = my_strdup(types[i]);
    }

    int error_val = valid_expression(tokens);
    printf("error_val = %d\n", error_val);
    return 0;
}