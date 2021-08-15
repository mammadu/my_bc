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
        tokens* tokens = tokenizer(argv[1]);
        int error_val = valid_expression(tokens);

        if (error_val != 0)
        {
            printf("(standard_in): syntax error\n");
            return SYNTAX_ERROR;
        }
        // print_tokens(tokens);

        shunting_yard* rpn = my_rpn(tokens);
        //print_output_queue(rpn);

        my_tree* final_tree = tree_expression_solver(rpn);

        free(final_tree);
        // ast_node* root = parser_tree(tokens);
        // int result = resolve_tree(root);
        // print("%d\n");
        free_token(tokens);
        free_shunting_yard(rpn);

        return 0;
    }
    else
    {
        printf("input not found, use quotation marks around your calculation");
        return INPUT_STRING_ERROR;
    }
}