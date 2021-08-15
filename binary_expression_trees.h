#ifndef binary_expression_trees_H
#define binary_expression_trees_H


#include "shunting_yard.h"
#include "my_c_functions.h"


#define ROOT 0
#define RIGHT 1
#define LEFT 2
#define DECIMAL_BASE 10


typedef struct tree
{
    char *value;
    int use;
    struct tree *left;
    struct tree *right;
} my_tree;


int leaves_checker(my_tree* node);

int tree_index_evaluation(int tree_index);

my_tree* node_solver(my_tree* node);

void free_tree(my_tree** tree_array, int size);

my_tree *tree_initializer(char *value);

my_tree* tree_expression_solver(shunting_yard* syd);

int tree_solver(my_tree* expression_tree_root);

char* expression_resolver(char* left_leaf, char* root, char* right_leaf);

my_tree* tree_pointer_finder(my_tree** tree_array, int value, int size);

void leaves_init(my_tree **tree_array, my_tree **temp_tree, my_tree *temporal_root, int i, int tree_index, int tree_array_len); 


#endif