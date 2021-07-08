CC = gcc
CFLAGS += -Wall -Wextra -g3 -Werror
CFLAGS_MEM = ${CFLAGS} -fsanitize=address
NAME = my_bc
OBJECT_FILES = my_c_functions.o my_bc.o


all: my_bc

${NAME}: ${OBJECT_FILES}
	${CC} -o $@ $^ ${CFLAGS_MEM}

%.o: %.c %.h
	${CC} ${CFLAGS} -c $< 

clean:
	rm -f *.o core.* 

re: clean ${NAME}