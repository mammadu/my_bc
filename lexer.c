#include "lexer.h"


int my_isdigit(int c)
{
    return (c >= '0' && c <= '9');
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

char** token_extractor(char* source, int token_count)
{
    char** tokens =  malloc(sizeof(char*) * token_count);


    return tokens;
}

char** token_type_extractor(char* source, int token_count)
{
    char** tokens_type =  malloc(sizeof(char*) * token_count);


    return tokens_type;
}

tokens* tokenizer(char* source)
{
    tokens* src_tokens = malloc(sizeof(tokens));
    tokens->token_count = tokens_counter(source);
    tokens->tokens = token_extractor(source, tokens->token_count);
    tokens->token_type = token_type_extractor(source, tokens->token_count);

    return src_tokens;
}

int main ()
{
    printf("%d", tokens_counter("1122+2*(3-424)/5"));
    return 0;
}
//Starting up branch
