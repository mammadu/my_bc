#include "lexer.h"
#define FIRST_CHAR 0
void token_strings_initializer(char** src ,int strings_count , int len)
{
    int i = 0, j = 0;

    while (i < strings_count)
    {
        src[i] = malloc(sizeof(char) * len);
        while (j < len)
        {
            src[i][j] = '\0';
            j += 1;
        }
        j = 0;
        i += 1;
    }
}

//returns amount of tokens in string
    //use to allocate memory in a char** later on
int tokens_counter(char* source)
{
    int token_amount = 0;
    int nonconsecutive_number = 0;
    
    for (int i =0; source[i] != '\0'; i += 1)
    {
        if(my_isdigit(source[i]) && nonconsecutive_number == 0)
        {
            nonconsecutive_number = 1;
            token_amount += 1;
        } 
        else if (my_isdigit(source[i]) && nonconsecutive_number == 1)
            continue;
        else
        {
            nonconsecutive_number = 0;
            token_amount += 1;
        }
    }
    return token_amount;
}

int number_extractor( char* source, char* dst, int index)
{
    int i = index, j = 0;
    char* temp = malloc(sizeof(char) * my_strlen(source));
    
    while(my_isdigit(source[i]))
    {
        temp[j] = source[i];
        
        j += 1;
        i += 1;
    }
     
    temp[j] = '\0';

    dst = my_strcpy(dst, temp);
    free(temp);

    return i - index;
}

char** token_extractor(char* source, int token_count)
{
    char** tokens =  malloc(sizeof(char*) * token_count);
    token_strings_initializer(tokens, token_count, my_strlen(source));
    int token_index = 0;

    for (int i = 0; source[i] != '\0'; i += 1)
    {
        if(my_isdigit(source[i]))
        {
            i += number_extractor(source, tokens[token_index], i);     
            token_index+= 1;
            if (source[i] == '\0')
                break;
        }
        
        tokens[token_index][0] = source[i];        
         token_index+= 1;
    }
    return tokens;
}

char** token_type_extractor(char** tokens, int token_count, char* source)
{
    char** tokens_type =  malloc(sizeof(char*) * token_count);
    token_strings_initializer(tokens_type, token_count, my_strlen(source));    
    
    for(int i = 0; i < token_count; i += 1)
    {
        if (my_isdigit(tokens[i][FIRST_CHAR]))
            tokens_type[i] = my_strcpy(tokens_type[i], VAL);
        else if (tokens[i][FIRST_CHAR] == '+')
            tokens_type[i] = my_strcpy(tokens_type[i], ADD);
        else if (tokens[i][FIRST_CHAR] == '-')
            tokens_type[i] = my_strcpy(tokens_type[i], SUB);
        else if (tokens[i][FIRST_CHAR] == '*')
            tokens_type[i] = my_strcpy(tokens_type[i], MULT);
        else if (tokens[i][FIRST_CHAR] == '/')
            tokens_type[i] = my_strcpy(tokens_type[i], DIV);
        else if (tokens[i][FIRST_CHAR] == '%')
            tokens_type[i] = my_strcpy(tokens_type[i], MOD);
        else if (tokens[i][FIRST_CHAR] == ' ')
            tokens_type[i] = my_strcpy(tokens_type[i], SPACE);
        else if (tokens[i][FIRST_CHAR] == '(')
            tokens_type[i] = my_strcpy(tokens_type[i], OPEN_PAR);
        else if (tokens[i][FIRST_CHAR] == ')')
            tokens_type[i] = my_strcpy(tokens_type[i], CLOSE_PAR);
        else
            tokens_type[i] = my_strcpy(tokens_type[i], UNKNOWN);
    }

    return tokens_type;
}

int* token_priority(tokens* tokens)
{
    int* token_priorities = malloc(sizeof(int) * tokens->token_count);
    
    for(int i = 0; i < tokens->token_count; i += 1)
    {
        // token_priorities[i] = malloc(sizeof(int) * len);
        if (my_isdigit(tokens->tokens[i][FIRST_CHAR]))
            token_priorities[i] = PRIORITY_ZERO;
        else if (tokens->tokens[i][FIRST_CHAR] == '+' || tokens->tokens[i][FIRST_CHAR] == '-')
            token_priorities[i] = PRIORITY_TWO;
        else if (tokens->tokens[i][FIRST_CHAR] == '*' || tokens->tokens[i][FIRST_CHAR] == '/' || tokens->tokens[i][FIRST_CHAR] == '%')
            token_priorities[i] = PRIORITY_THREE;
        else if (tokens->tokens[i][FIRST_CHAR] == '(')
            token_priorities[i] = PRIORITY_ONE;
        else if (tokens->tokens[i][FIRST_CHAR] == ')')
            token_priorities[i] = PRIORITY_FOUR;
        else
            token_priorities[i] = NO_PRIORITY;
    }
    return token_priorities;
}

void print_tokens(tokens* tokens)
{
    for (int i = 0; i < tokens->token_count; i++)
    {
        printf("%s\n", tokens->token_type[i]);
        printf("%s\n", tokens->tokens[i]);
        printf("%d\n", tokens->token_priority[i]);
    }
}

tokens* tokenizer(char* source)
{
    tokens* src_tokens = malloc(sizeof(tokens));

    src_tokens->token_count = tokens_counter(source);
    
    src_tokens->tokens = token_extractor(source, src_tokens->token_count);

    src_tokens->token_type = token_type_extractor(src_tokens->tokens, src_tokens->token_count, source);

    src_tokens->token_priority = token_priority(src_tokens);


    return src_tokens;
}

void free_token(tokens* tokens)
{
    int i = 0; 

    while(i < tokens->token_count)
    {
        free(tokens->tokens[i]);
        free(tokens->token_type[i]);
        i += 1;
    }
    free(tokens->tokens);
    free(tokens->token_type);
    free(tokens);
}

// int main ()
// {
//     tokens* tok = tokenizer("1122+2*(3-424)/5"); 
//     int i = 0;
//     while (i < tok->token_count)
//     {
//         printf("%s\n", tok->tokens[i]);
//         printf("%s\n", tok->token_type[i]);
//         printf("%d\n", tok->token_priority[i][0]);
//         printf("\n");
//         i += 1;
//     }

//     return 0;
// }
//Starting up branch
