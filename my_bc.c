#include "my_bc.h"

/*
A valid expression:

• must only contain the operators +, -, *, /, and %
• must only have integer values
• can contain parentheses, but each group must be properly closed
• can contain spaces

Since we are doing whole number arithmetic, 
    divisions are euclidian keeping only the quotient, 
        while the remainder can be obtained with a modulo operation.
*/

int main(int argc, char* argv[])
{
    if(argc > 1 && argc < 3) //run if there is an argument with a string 
    {
        //first call lexer function on string,
            //It should return an array of arrays with all the Tokens found in the string

        tokens* tokens = lexer(argv[0][1]); 
        

    } 
    return 0;
}