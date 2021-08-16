#include "binary_expression_trees.h"

//return 0 if both leaves are NULL or 1 if there is at least a left or right node 
int leaves_checker(my_tree* node)
{
    int leaf_check = 0;
    if(node->left != NULL || node->right != NULL)
        leaf_check = 1;
    
    return leaf_check;
}

my_tree *tree_initializer(char *value)
{
    my_tree *new_tree;
    if ((new_tree = malloc(sizeof(my_tree))) == NULL)
        printf("Nothing on tree\n");
    
    //initialize tree value
    new_tree->value = my_strdup(value);
    new_tree->use = 0;
        
    new_tree->left = NULL;
    new_tree->right = NULL;

    return new_tree;
}

void free_tree(my_tree** tree_array, int tree_size )
{
    for(int i = 0; i < tree_size; i++)
    {
        printf(" i = %d value %s\n", i,tree_array[i]->value);
    }
    free(tree_array);
}

my_tree **pop_tree_array(my_tree **tree_array, int size)
{
    my_tree** new_tree_array = malloc(sizeof(my_tree *) * size);

    if (size > 3)
    {
        for(int i = 0; i < size - 3; i++)
        {
            new_tree_array[i]->value = my_strdup(tree_array[i]->value);
            new_tree_array[i]->use = tree_array[i]->use;
            new_tree_array[i]->left = tree_array[i]->left;
            new_tree_array[i]->right = tree_array[i]->right;
        }
    }
    return new_tree_array;
}

int leaves_division(int left, int right, int result)
{
    if (right == 0)
        result = 0;
    else
        result = left / right;
    return result;
}

char* expression_resolver(char* left_leaf, char* root, char* right_leaf)
{
    int left = my_atoi_base(left_leaf, DECIMAL_BASE);
    int right = my_atoi_base(right_leaf, DECIMAL_BASE);
    int result = 0;

    if(my_strcmp(root, "+") == 0)
        result = left + right;
    else if(my_strcmp(root, "-") == 0)
        result = left - right;
    else if(my_strcmp(root, "*") == 0)
        result = left * right;
    else if(my_strcmp(root, "/") == 0)
        result = leaves_division(left, right, result);
    else
        result = left % right;

    char* resolution = my_itoa_base(result, DECIMAL_BASE);
    
    return resolution;
}

my_tree* node_solver(my_tree* node)
{
    char* resolution =  expression_resolver(node->left->value, node->value, node->right->value);

    free(node->left);
    free(node->right);
    node->left = NULL;
    node->right = NULL;
    free(node->value);
    node->value = my_strdup(resolution);
    free(resolution);
    
    return node;
}

my_tree* node_error(my_tree* node)
{
    free(node->right->value);
    free(node->left->value);
    node->left->value = NULL;
    node->right->value = NULL;
    free(node->left);
    free(node->right);
    node->left = NULL;
    node->right = NULL;
    free(node->value);
    node->value = my_strdup("ERROR");
    return node;
}

int division_error(my_tree* node)
{
    if(node->right->value != NULL && my_strcmp(node->value, "/") == 0 && my_strcmp(node->right->value, "0") == 0)
        return 1;
    return 0;
}

int tree_error(my_tree* expression_tree_root)
{
    int exit = 0;

    while(leaves_checker(expression_tree_root) > 0)
    {
        if(expression_tree_root->left != NULL && leaves_checker(expression_tree_root->left) == 1)
            tree_error(expression_tree_root->left); 
        
        if(expression_tree_root->right != NULL && leaves_checker(expression_tree_root->right) == 1)
            tree_error(expression_tree_root->right);

        if (division_error(expression_tree_root) == 1 || my_strcmp(expression_tree_root->right->value, "ERROR") == 0 || my_strcmp(expression_tree_root->left->value, "ERROR") == 0)
            expression_tree_root = node_error(expression_tree_root);
        else   
            expression_tree_root = node_solver(expression_tree_root);
    }
    
    if(my_strcmp(expression_tree_root->value, "ERROR") == 0) 
        exit = 1;
       
    return exit;
}

int tree_solver(my_tree* expression_tree_root)
{
    while(leaves_checker(expression_tree_root) > 0)
    {
        if(expression_tree_root->left != NULL && leaves_checker(expression_tree_root->left) == 1)
            tree_solver(expression_tree_root->left); 
        
        if(expression_tree_root->right != NULL && leaves_checker(expression_tree_root->right) == 1)
            tree_solver(expression_tree_root->right);
         
        expression_tree_root = node_solver(expression_tree_root);
    }

    return my_atoi_base(expression_tree_root->value, DECIMAL_BASE);
}

int tree_index_evaluation(int tree_index)
{
    int minus = - 2;
    if (tree_index == 0)
        minus = 0;
    else if(tree_index == 1) 
        minus = -1;
    
    return minus;
}

// my_tree* tree_expression_solver(shunting_yard* syd)
// {
//     int tree_index = 0;
//     my_tree *temporal_root;
//     my_tree **tree_array = malloc(sizeof(my_tree*) * tree_size);
//     my_tree **temp_tree = malloc(sizeof(my_tree*) * tree_size);
    
//     for (int i = 0; i < syd->output_queue_count; i++)
//     {
//         temporal_root = tree_initializer(syd->output_queue[i]);
//         temp_tree[i] = tree_initializer(syd->output_queue[i]);
//         if (my_str_is_numeric(syd->output_queue[i]) == 0)
//         {
//             leaves_init(tree_array, temp_tree, temporal_root, i, tree_index, syd->output_queue_count); 
//             tree_array = pop_tree_array(tree_array, tree_index);
//             tree_index +=  tree_index_evaluation(tree_index);
//         }
//         tree_array[tree_index] = temporal_root;
//         tree_index += 1;
//     }
//     if (tree_error(tree_array[ROOT]) == 1)
//         printf("%s\n", ERROR_DIVISION);
//     else
//         printf("%d\n", tree_solver(tree_array[ROOT])); 

//     free_tree(temp_tree, syd->output_queue_count);
//     return tree_array[ROOT];

// }
my_tree **tree_array_initializer(shunting_yard* syd)
{
    my_tree** new_tree_array = malloc(sizeof(my_tree*) * syd->output_queue_count);

    for(int i = 0; i < syd->output_queue_count; i++)
        new_tree_array[i] = tree_initializer(syd->output_queue[i]);
    
    return new_tree_array;
}

void leaves_init(my_tree **tree_array, int index) 
{
    int use_counter = 0;

    if (index == 0)
    {
        tree_array[index]->left = tree_initializer("0");
        tree_array[index]->right = tree_initializer("0");
    }
    else if(index == 1)
    {
        tree_array[ROOT]->use = 1;
        tree_array[index]->right = tree_array[ROOT];
        tree_array[index]->left = tree_initializer("0");
    }
    
    for(int i = index - 1; i >= 0 && use_counter < 2; i--)
    {
        if(tree_array[i]->use == 0 && use_counter == 0)
        {
            tree_array[index]->right = tree_array[i];
            tree_array[i]->use = 1;
            use_counter += 1;
        } 
        else if (tree_array[i]->use == 0 && use_counter == 1)
        {
            tree_array[index]->left = tree_array[i];
            tree_array[i]->use = 1;
            use_counter += 1;
        }
    }
}

my_tree* tree_pointer_finder(my_tree** tree_array, int size)
{
    my_tree* node;
    for(int i = 0; i < size; i++)
    {
        if(tree_array[i]->use == 0)
        {
            node = tree_array[i];
            break;
        }
    }
    return node;
}

my_tree* tree_expression_solver(shunting_yard* syd)
{
    my_tree **tree_array = tree_array_initializer(syd);

    for (int i = 0; i < syd->output_queue_count; i++)
        if (my_str_is_numeric(syd->output_queue[i]) == 0)
            leaves_init(tree_array, i); 
    
    my_tree *root = tree_pointer_finder(tree_array, syd->output_queue_count);

    if (tree_error(root) == 1)
        printf("%s\n", ERROR_DIVISION);
    else
        printf("%d\n", tree_solver(root)); 

    //free_tree(tree_array, syd->output_queue_count);
    free(tree_array);
    return root;
}