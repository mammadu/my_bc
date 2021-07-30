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
    error_val = error_val + spaces_between_numbers(tokens);
    error_val = error_val + non_val_after_open_par(tokens);
    error_val = error_val + non_val_before_close_par(tokens);

    //below lines are for debugging
    // printf("[debug]invalid_characters = %d\n", invalid_characters(tokens));
    // printf("[debug]consecutive_operators = %d\n", consecutive_operators(tokens));
    // printf("[debug]invalid_parentheses = %d\n", invalid_parentheses(tokens));
    // printf("[debug]spaces_between_numbers = %d\n", spaces_between_numbers(tokens));
    // printf("[debug]non_val_after_open_par = %d\n", non_val_after_open_par(tokens));
    // printf("[debug]non_val_before_close_par = %d\n", non_val_before_close_par(tokens));


    return error_val;
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

int is_unknown(char* token_type)
{
    if(my_strcmp(token_type, UNKNOWN) == SAME)
    {
        return 1;
    }
    return 0;
}

int invalid_characters(tokens* tokens) //check the number token to make sure only digits 0-9 are in the string
{
    for (int i = 0; i < tokens->token_count; i++) //loop to go through every token
    {
        if (is_unknown(tokens->token_type[i])) //check if the token is a UNKNOWN
        {
            return 1;
        }
    }
    return 0; //otherwise return 1 meaning the string has invalid characters
}

int next_non_space_index(tokens* token, int current_index)
{
    /*
    returns the index of the next non-space
    */
    int i = current_index + 1;
    while (i < token->token_count)
    {

        // printf("[debug]i = %d\n",i);        
        if (!(is_space(token->token_type[i])))
        {
            break;
        }
        i++;
    }
    return i;
}

int previous_non_space_index(tokens* token, int current_index)
{
    /*
    returns the index of the previous non-space
    */
    int i = current_index - 1;
    while (i > 0)
    {
        if (!(is_space(token->token_type[i])))
        {
            break;
        }
        i--;
    }
    return i;
}

int spaces_between_numbers(tokens* token)
{
    /*if there is a VAL token followed by one or more SPACE tokens, 
    there should not be another VAL or OPEN_PAR token next
    */

    for (int i = 0; i < token->token_count; i++)
    {
        if (is_val(token->token_type[i])) //check if current token is a VAL
        {
            int next_non_space = next_non_space_index(token, i);
            // printf("[debug]next_non_space = %d\n", next_non_space);
            // printf("[debug]is_operand(token->token_type[i]) = %s\n", token->token_type[i]);
            if (next_non_space == token->token_count || is_operand(token->token_type[next_non_space]) || is_close_par(token->token_type[next_non_space])) //case where the value is followed by only spaces
            {
                // printf("[debug]we made it to line 234");
                continue;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int consecutive_operators(tokens* token) //checks if there are multiple operators consecutively
{
    for (int i = 0; i < token->token_count - 1; i++) //loop to go through every token
    {
        if (is_operand(token->token_type[i])) //check if the token is an operand
        {
            int next_non_space = next_non_space_index(token, i); //can possibly optimize by making i==to next non space at end of if statement
            if(!is_sub(token->token_type[next_non_space]) && is_operand(token->token_type[next_non_space]))
            {
                return 1;
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


int non_val_after_open_par(tokens* token)
{
    for (int i = 0; i < token->token_count; i++)
    {
        if (is_open_par(token->token_type[i]))
        {
            int next_non_space = next_non_space_index(token, i);
            if (next_non_space == token->token_count || (!is_val(token->token_type[next_non_space]) && !is_sub(token->token_type[next_non_space]) && !is_open_par(token->token_type[next_non_space])))
            {
                return 1;
            }
            else
            {
                continue;
            }
        }
    }
    return 0;
}

int non_val_before_close_par(tokens* token)
{
    for (int i = 0; i < token->token_count; i++)
    {
        if (is_close_par(token->token_type[i]))
        {
            int previous_non_space = previous_non_space_index(token, i);
            if (!is_close_par(token->token_type[previous_non_space]) && !is_val(token->token_type[previous_non_space]))
            {
                return 1;
            }
            else
            {
                continue;
            }
        }
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
// int main()
// {
//     tokens* tokens = malloc(sizeof(tokens));

//     int str_count = 4;
    
//     char* str[str_count];
//     int i = 0;    
//     str[i] = ")";
//     i++;
//     str[i++] = "(";
//     i++;
//     str[i++] = ")";
//     i++;
//     str[i++] = ")";

//     char* types[str_count];
//     i = 0;
//     types[i] = CLOSE_PAR;
//     i++;
//     types[i] = OPEN_PAR;
//     i++;
//     types[i] = CLOSE_PAR;
//     i++;
//     types[i] = OPEN_PAR;

//     tokens->token_count = str_count;
//     tokens->tokens = malloc(tokens->token_count * sizeof(char*));
//     tokens->token_type = malloc(tokens->token_count * sizeof(char*));

//     for (int i = 0; i < tokens->token_count; i++)
//     {
//         tokens->tokens[i] = my_strdup(str[i]);
//         tokens->token_type[i] = my_strdup(types[i]);
//     }

//     int error_val = valid_expression(tokens);
//     printf("error_val = %d\n", error_val);
//     return 0;
// }