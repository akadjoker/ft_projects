
TEST_PROGRAM = teste

CC = gcc
CFLAGS = -Wall  -I../include 

LIB = ../libft_malloc.a   ../libft/libft.a

TEST_SRC = teste.c


LDFLAGS = $(LIB)


$(TEST_PROGRAM): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC)   $(LDFLAGS) -o $(TEST_PROGRAM)
	MALLOC_DEBUG=1  ./$(TEST_PROGRAM)  

run: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

gdb:
	gdb --args env LD_PRELOAD=./libft_malloc.so ./$(TEST_PROGRAM)

val:
	valgrind --leak-check=full env LD_PRELOAD=./libft_malloc.so ./$(TEST_PROGRAM)


clean:
	rm -f $(TEST_PROGRAM)

.PHONY: clean run

