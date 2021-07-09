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
    int i = 0;

    if(argc > 1 && argc < 3)
    {
        while(argv[1][i] != '\0')
        {
            printf("%c", argv[1][i]);
            i += 1;
        }
    } 
    return 0;
}