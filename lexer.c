#include "lexer.h"
#include "my_c_functions.c"


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
    char* temp;
    while(my_isdigit(source[i]))
    {
        temp[j] = source[i];
        j += 1;
        i+= 1;
    }

    dst = my_strdup(temp);
    return i - index;
}

char** token_extractor(char* source, int token_count)
{
    char** tokens =  malloc(sizeof(char*) * token_count);
    int token_index = 0, index_move = 0;
    for (int i = 0; source[i] != '\0'; i += 1)
    {
        if(my_isdigit(source[i]))
        {
            i += number_extractor(source, tokens[token_index], i);
            token_index+= 1;
        } 
        // else
        // {

        // }
    }
    return tokens;
}

//To be implemented 
char** token_type_extractor(char** tokens, int token_count)
{
    char** tokens_type =  malloc(sizeof(char*) * token_count);


    return tokens_type;
}

tokens* tokenizer(char* source)
{
    tokens* src_tokens = malloc(sizeof(tokens));

    src_tokens->token_count = tokens_counter(source);
    
    src_tokens->tokens = token_extractor(source, src_tokens->token_count);
    printf("HOLA");

    //tokens->token_type = token_type_extractor(source, tokens->token_count);

    return src_tokens;
}

int main ()
{

    tokens* tok = tokenizer("1122+2*(3-424)/5"); 
    printf("%d", tokens_counter("1122+2*(3-424)/5"));
    return 0;
}
//Starting up branch
