#include "binary_expression_trees.h"

//return 0 if both leaves are NULL or 1 if there is at least a left or rigth node 
int leaves_checker(my_tree* node)
{
    int leaf_check = 0;
    
    if(node->left != NULL || node->rigth != NULL)
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
    new_tree->rigth = NULL;

    return new_tree;
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

    return new_tree_array;
}

my_tree* tree_pointer_finder(my_tree** tree_array, int value, int size)
{
    for(int i = 0; i < size; i++ )
    {
        if(my_atoi_base(tree_array[i]->value, DECIMAL_BASE) == value && tree_array[i]->use == 0)
        {
            tree_array[i]->use = 1;
            return tree_array[i]; 
        }
    }
}

//add tokens as trees to each index of tree array
    //if token is an operator
        //make tree duplicates of prior 2 tokens
        //index of token that is 2 before current is now duplicate of operator token tree
        //free tree of index one before and operator tree.

my_tree* tree_duplicate(my_tree* tree)
{
    my_tree* duplicate = malloc(sizeof(my_tree));
    duplicate->value = my_strdup(tree->value);
    duplicate->left = tree->left;
    duplicate->rigth = tree->rigth;
    return duplicate;
}

my_tree* tree_maker(shunting_yard* syd)
{
    int tree_index = 0;
    my_tree *temporal_root;
    my_tree **tree_array = malloc(sizeof(my_tree *) * syd->output_queue_count);
    my_tree **temp_tree = malloc(sizeof(my_tree *) * syd->output_queue_count);
    
    for (int i = 0; i < syd->output_queue_count; i++)
    {
        // temporal_root = tree_initializer(syd->output_queue[i]);
        // temp_tree[i] = tree_initializer(syd->output_queue[i]);
        
        tree_array[tree_index] = tree_initializer(syd->output_queue[i]);

        //if syd->output_queue[i] is not numeric == operator
        if (my_str_is_numeric(syd->output_queue[i]) == 0)
        {
            tree_array[tree_index]->left = tree_duplicate(tree_array[tree_index - 2]);
            tree_array[tree_index]->rigth = tree_duplicate(tree_array[tree_index - 1]);
            free(tree_array[tree_index - 2]);
            free(tree_array[tree_index - 1]);

            tree_array[tree_index - 2] = tree_duplicate(tree_array[tree_index]);

            free(tree_array[tree_index]);

            tree_index -= 2;
            // //printf("%s\n", tree_array[tree_index - 1]->value);
            // int left = my_atoi_base(tree_array[tree_index - LEFT]->value, DECIMAL_BASE);
            // int rigth =  my_atoi_base(tree_array[tree_index - RIGTH]->value, DECIMAL_BASE);
            // temporal_root->left = tree_pointer_finder(temp_tree, left , syd->output_queue_count);
            // temporal_root->rigth = tree_pointer_finder(temp_tree, rigth, syd->output_queue_count);

            // tree_array = pop_tree_array(tree_array, syd->output_queue_count);
            // tree_index -= 2;
        }

        tree_index += 1;


        // tree_array[tree_index] = temporal_root;
        //printf("%s\n", tree_array[tree_index]->value);

        tree_index += 1;
    }
    
    printf("Root %s\n rigth %s\n left %s\n", tree_array[ROOT]->value, tree_array[ROOT]->rigth->value, tree_array[ROOT]->left->value);

    free(temporal_root);
    //free tree_array PENDING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return tree_array[ROOT];
}


char* expression_resolver(char* left_leaf, char* root, char* rigth_leaf)
{
    int left = my_atoi_base(left_leaf, DECIMAL_BASE);
    int rigth = my_atoi_base(rigth_leaf, DECIMAL_BASE);
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

my_tree* node_solver(my_tree* node)
{

    char* resolution =  expression_resolver(node->left->value, node->value, node->rigth->value);
    node->left = NULL;
    node->rigth = NULL;
    free(node->value);
    node->value = my_strdup(resolution);

    return node;
}

int tree_solver(my_tree* expresion_tree_root)
{
    my_tree* temporal_root = expresion_tree_root;
    my_tree* anterior_root = expresion_tree_root;

    while(leaves_checker(temporal_root) > 0)
    {
        if(temporal_root->left != NULL)
        {
            anterior_root = temporal_root;
            temporal_root = temporal_root->left; 
        }
        if(temporal_root->rigth != NULL)
        {
            anterior_root = temporal_root;
            temporal_root = temporal_root->rigth; 
        }
    }

    if(anterior_root->rigth != NULL && leaves_checker(anterior_root->rigth) == 1)
         tree_solver(anterior_root->rigth);
    else
        anterior_root = node_solver(anterior_root);

    if(anterior_root != expresion_tree_root)
        tree_solver(expresion_tree_root);

    return my_atoi_base(anterior_root->value, DECIMAL_BASE);
}

int main()
{
    int rpn_size = 9;
    char *rpn[] = {"1", "2", "3", "42", "-", "*", "5", "%", "+"};

    shunting_yard* syd = malloc(sizeof(shunting_yard));
    
    syd->output_queue_count = 9;
    syd->output_queue = malloc(sizeof(char*) * syd->output_queue_count * 10);


    for (int i = 0; i < rpn_size; i+=1)
        syd->output_queue[i] = my_strdup(rpn[i]);

    
    my_tree* test_tree = tree_maker(syd);
    int solution = tree_solver(test_tree);

    printf("%d", solution);   
    
    return 0;
}