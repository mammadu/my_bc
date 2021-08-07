#ifndef parser_H
#define parser_H

typedef struct ast_node 
{

enum { ADD, SUB, MULT, DIV, MOD, VAL };

    union
    {
        int value;

        struct
        {
            struct ast_node* left;
            struct ast_node* right;
        }op;
    }ast_node;

}

#endif