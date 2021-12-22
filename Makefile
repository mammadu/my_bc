# The compiler: gcc for C programs
CC = gcc

# Compiler flags:
CFLAGS += -Wall -Wextra -g3 -Werror
CFLAGS_MEM = ${CFLAGS} -fsanitize=address

# headers file
HEADER += include/my_bc.h include/lexer.h include/binary_expression_trees.h include/my_c_functions.h include/shunting_yard.h include/valid_expression.h

# All the .o files we need for our executable.
OBJECT_FILES = obj/my_c_functions.o obj/my_bc.o obj/valid_expression.o obj/lexer.o obj/shunting_yard.o obj/binary_expression_trees.o 

NAME = my_bc

all: my_bc

${NAME}: ${OBJECT_FILES}
	${CC} -o $@ $^ ${CFLAGS}


# A "phony" target to remove built files and backups
obj/%.o: src/%.c include/%.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) obj/* ./my_bc core.* 

re: clean ${NAME}