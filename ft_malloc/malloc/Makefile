# Nome do executável
TARGET = main

CC = gcc
CFLAGS = -Wall -Wextra -g -I./include -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^
	@./$(BINDIR)/$(TARGET)
	



$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@


run:
	./$(BINDIR)/$(TARGET)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Limpar e recompilar tudo
re: clean all





val:
	valgrind --leak-check=full  ./$(TEST_PROGRAM)





.PHONY: clean run

