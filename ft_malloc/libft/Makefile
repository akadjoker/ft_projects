CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
OBJDIR = obj
SRC_DIR = src
DEPS = include/libft.h include/ft_rbt.h
NAME = libft.a


SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# Debug info
$(info == Debug Information ==)
$(info Source files: $(SRC))
$(info Object files: $(OBJ))
$(info =====================)

all: mk_objdir $(NAME)

mk_objdir:
	@mkdir -p $(OBJDIR)
	@echo "Created object directory: $(OBJDIR)"

# Regra de compilação com mais informações
$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@echo "\033[1;34m  Compiling [$< to $@]\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Creating library $(NAME)..."
	@ar rcs $@ $(OBJ)
	@echo "\033[1;36m$@ is built!\033[0m"

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@echo "\033[1;33m$(NAME) objects removed.\033[0m"

fclean: clean
	@echo "Removing library..."
	@rm -f $(NAME)
	@echo "\033[1;33m$(NAME) removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re mk_objdir

# Regra para verificar a estrutura do projeto
check:
	@echo "\nChecking project structure..."
	@echo "Current directory: $$(pwd)"
	@echo "\nChecking source directory ($(SRC_DIR)):"
	@ls -la $(SRC_DIR)
	@echo "\nChecking include directory:"
	@ls -la include
	@echo "\nChecking if headers exist:"
	@for header in $(DEPS); do \
		if [ -f $$header ]; then \
			echo "$$header exists"; \
		else \
			echo "$$header does not exist"; \
		fi \
	done