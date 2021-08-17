# my_bc

# How to write github Readmes
https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax

# lexer information
https://en.wikipedia.org/wiki/Lexical_analysis

# Parser information
https://en.wikipedia.org/wiki/Parsing

# Reverse polish notation converter/evaluator
https://www.dcode.fr/reverse-polish-notation

# Shunting-yard algorithm
https://en.wikipedia.org/wiki/Shunting-yard_algorithm


# Insert link showing parse tree for calculation
Struct use as reference for the AST on my_bc:
https://stackoverflow.com/questions/21150454/representing-an-abstract-syntax-tree-in-c#21150567

struct ast_node {
  enum { CONSTANT, ADD, SUB, ASSIGNMENT } class;
  union { int                                 value;
          struct { struct ast_node* left;    
                   struct ast_node* right;  } op;
};


# TODO
Figure out how to deal with negative numbers