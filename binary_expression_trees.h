#ifndef binary_expression_trees_H
#define binary_expression_trees_H


#include "shunting_yard.h"
#include "my_c_functions.h"

#define ROOT 0
#define RIGTH 1
#define LEFT 2
#define DECIMAL_BASE 10


typedef struct tree
{
    char *value;
    struct tree *left;
    struct tree *rigth;
} my_tree;

int leaves_checker(my_tree* node);

my_tree *tree_initializer(char *value);

my_tree* tree_maker(shunting_yard* syd);

int tree_solver(my_tree** expresion_tree);

char* expression_resolver(char* left_leaf, char* root, char* rigth_leaf);

#endif