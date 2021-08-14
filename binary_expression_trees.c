#include "binary_expression_trees.h"

//return 0 if both leaves are NULL or 1 if there is at lease a node left or rigth 
int leaves_checker(my_tree* node)
{
    int leaf_check = 0;
    
    if(node->left != NULL || node->rigth != NULL)
        leaf_check = 1
    
    return leaf_check
}

my_tree *tree_initializer(char *value)
{
    my_tree *new_tree;

    if ((new_tree = malloc(sizeof(my_tree))) == NULL)
        printf("Nothing on tree\n");
    
    //initialize tree value
    new_tree->value = strdup(value);

    if ((new_tree->left = malloc(sizeof(my_tree *))) == NULL || (new_tree->rigth = malloc(sizeof(my_tree *))) == NULL)
        printf("Nothing on leaves\n");
        
    new_tree->left = NULL;
    new_tree->rigth = NULL;

    return new_tree;
}

my_tree* tree_maker(shunting_yard* syd)
{
    int tree_index = 0;
    my_tree *temporal_root;
    my_tree **tree_array = malloc(sizeof(my_tree *) * syd->output_queue_count);
    
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        temporal_root = tree_initializer(syd->output_queue[i]);

        if (my_str_is_numeric(syd->output_queue[i]) == 0)
        {
            temporal_root->left = tree_array[tree_index - LEFT];
            temporal_root->rigth = tree_array[tree_index - RIGTH];
            tree_index -= 2;
        }

        tree_array[tree_index] = temporal_root;
        tree_index += 1;
        printf("%s\n", tree_array[i]->value);
    }
    free(temporal_root);
    //free tree_array PENDING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return tree_array[ROOT];
}


char* expression_resolver(char* left_leaf, char* root, char* rigth_leaf)
{
    int left = my_atoi_base(left_leaf);
    int rigth = my_atoi_base(rigth_leaf);
    int result = 0;

    if(my_strcmp(root, "+") == 0)
        result = left + rigth;
    else if(my_strcmp(root, "-") == 0)
        result = left - rigth;
    else if(my_strcmp(root, "*") == 0)
        result = left * rigth;
    else if(my_strcmp(root, "/") == 0)
        result = left / rigth;
    else if(my_strcmp(root, "%") == 0)
        result = left % rigth;

    char* resolution = my_itoa_base(result, DECIMAL_BASE);
    
    return resolution;
}

int tree_solver(my_tree* expresion_tree_root)
{
    
}

int main()
{
    int rpn_size = 9;
    char *rpn[] = {"1", "2", "3", "42", "-", "*", "5", "%", "+"};
    //stack of trees
 
    
    return 0;
}