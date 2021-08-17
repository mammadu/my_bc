CC = gcc
CFLAGS += -Wall -Wextra -g3 -Werror
CFLAGS_MEM = ${CFLAGS} -fsanitize=address
NAME = my_bc
OBJECT_FILES = my_c_functions.o my_bc.o valid_expression.o lexer.o shunting_yard.o binary_expression_trees.o #parser.o
TEST = valid_expression
TEST_FILES = my_c_functions.o valid_expression.o lexer.o

all: my_bc

${NAME}: ${OBJECT_FILES}
	${CC} -o $@ $^ ${CFLAGS_MEM}

test: ${TEST_FILES}
	${CC} -o ${TEST} $^ ${CFLAGS}

%.o: %.c %.h
	${CC} ${CFLAGS} -c $< 

clean:
	rm -f *.o core.* 

re: clean ${NAME}