# my_bc in C programming language
 
- This is a simple and custom bc implementation in the C programming language, my_bc -- calculates an infix Arithmetic expression passed as a String.
 
-my_bc support number, parentheses, and the operators ( +, -, *, /, %).
 
-This implementation is extremely optimized for under-powered computers.
 
-For a deeper understanding of my_bc logic flow please refer to its diagram my_bc_diagram.jpg
 
# Authorized function(s)
 
- malloc(3)
- free(3)
- printf(3)
- write(2)
 
# **** Instruction on how to compile and use my_bc ****

1. Because I created a makefile for this program, you can compile the files by typing "make"

2. It will give you the output "my_bc"

3. See example to resolve an Arithmetic expression:
    $>./my_bc "2 + 2"
    4
    $>
    
4. To clean/remove the .o files, type "make clean" in your terminal
 
# **** Useful documentation to understand my_bc **** 
- Lexer information: https://en.wikipedia.org/wiki/Lexical_analysis
 
- Parser information: https://en.wikipedia.org/wiki/Parsing
 
- Reverse polish notation converter/evaluator: https://www.dcode.fr/reverse-polish-notation
 
- Shunting-yard algorithm: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
 
- Binary Expression Trees: https://en.wikipedia.org/wiki/Binary_expression_tree
 

