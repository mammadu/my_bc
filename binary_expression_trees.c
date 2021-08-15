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

void free_tree(my_tree** tree_array, int size)
{
    int i = 0;

    while(i < size)
    {
        free(tree_array[i]);
        i += 1;
    }
    free(tree_array);

}

my_tree **pop_tree_array(my_tree **tree_array, int size)
{
    my_tree** new_tree_array = malloc(sizeof(my_tree *) * size);
    int i = 0;

    while(i < size - 3)
    {
        new_tree_array[i] = tree_array[i];
        i += 1;
    }
    //free_tree(tree_array, size);

    return new_tree_array;
}

my_tree* tree_pointer_finder(my_tree** tree_array, int value, int size)
{
    int i = 0;
    while(i < size)
    {
        if(my_atoi_base(tree_array[i]->value, DECIMAL_BASE) == value && tree_array[i]->use == 0)
        {
            tree_array[i]->use = 1;
            break;
        }
        i += 1;
    }
    return tree_array[i];
}

void leaves_init(my_tree **tree_array, my_tree **temp_tree, my_tree *temporal_root, int i, int tree_index, int tree_array_len) 
{
    if (tree_index == 0)
    {
        temporal_root->left = tree_initializer("0");
        temporal_root->right = tree_initializer("0");
    }
    else if(tree_index == 1)
    {

        int left =  my_atoi_base(tree_array[tree_index - RIGHT]->value, DECIMAL_BASE);

        temporal_root->right = tree_pointer_finder(temp_tree, left , tree_array_len);
        temporal_root->left = tree_initializer("0");
    }
    else
    {

    int left = my_atoi_base(tree_array[tree_index - LEFT]->value, DECIMAL_BASE); 

    int right =  my_atoi_base(tree_array[tree_index - RIGHT]->value, DECIMAL_BASE);

    //printf("%s tree index %d left %d right %d\n",tree_array[i -1]->right->value, tree_index, left, right);
    temporal_root->left = tree_pointer_finder(temp_tree, left , tree_array_len);

    temporal_root->right = tree_pointer_finder(temp_tree, right, tree_array_len);
    }

    temp_tree[i]->left = temporal_root->left;
    temp_tree[i]->right = temporal_root->right;
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

    return node;
}

my_tree* node_error(my_tree* node)
{
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

my_tree* tree_expression_solver(shunting_yard* syd)
{
    int tree_index = 0;
    my_tree *temporal_root;
    my_tree **tree_array = malloc(sizeof(my_tree *) * syd->output_queue_count);
    my_tree **temp_tree = malloc(sizeof(my_tree *) * syd->output_queue_count);
    
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        temporal_root = tree_initializer(syd->output_queue[i]);
        temp_tree[i] = tree_initializer(syd->output_queue[i]);
        if (my_str_is_numeric(syd->output_queue[i]) == 0)
        {
            leaves_init(tree_array, temp_tree, temporal_root, i, tree_index, syd->output_queue_count); 
            tree_array = pop_tree_array(tree_array, syd->output_queue_count);
            tree_index +=  tree_index_evaluation(tree_index);
        }
        tree_array[tree_index] = temporal_root;
        tree_index += 1;
    }
    if (tree_error(tree_array[ROOT]) == 1)
        printf("%s\n", ERROR_DIVISION);
    else
        printf("%d\n", tree_solver(tree_array[ROOT])); 

    return tree_array[ROOT];
}

// int main()
// {
//     int rpn_size = 9;
//     char *rpn[] = {"1", "2", "3", "42", "-", "*", "5", "%", "+"};

//     shunting_yard* syd = malloc(sizeof(shunting_yard));
    
//     syd->output_queue_count = 9;
//     syd->output_queue = malloc(sizeof(char*) * syd->output_queue_count * 10);


//     for (int i = 0; i < rpn_size; i+=1)
//         syd->output_queue[i] = my_strdup(rpn[i]);
    
//     my_tree* test_tree = tree_expression_solver(syd);
   
//     return 0;
// }