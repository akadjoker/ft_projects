NAME = ft_nm

# Diretórios
SRC_DIR = src
OBJDIR = obj
LIBFT_DIR = ./libft
INCLUDE_DIR = include
DEPS = include/ft_ls.h

# Libft
LIBFT = -L $(LIBFT_DIR) -lft

# Headers
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h) $(wildcard $(LIBFT_DIR)/*.h)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/include 

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SANITIZE = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer

# Arquivos fonte e objeto
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# Debug info
$(info == Debug Information ==)
$(info Sources: $(SRC))
$(info Objects: $(OBJ))
$(info Headers: $(HEADERS))
$(info =====================)

# Regras
all: mk_objdir libft $(NAME)

mk_objdir:
	@mkdir -p $(OBJDIR)
	@echo "Created object directory: $(OBJDIR)"

libft:
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

# Corrigido: mudou de $(OBJS) para $(OBJ)
$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(SANITIZE) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;32m$(NAME) built successfully!\033[0m"

# Corrigido: removido $(INCLUDES) dos pré-requisitos e corrigido (CC) para $(CC)
$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "\033[1;34m  Compiling [$< to $@]\033[0m"
	@$(CC) $(CFLAGS) $(SANITIZE) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Cleaning everything..."
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "\033[1;33mAll cleaned!\033[0m"

re: fclean all

check:
	@echo "\n\033[1;32m Checking project structure..."
	@echo "Current directory: $$(pwd)"
	@echo "\nChecking source directory ($(SRC_DIR)):"
	@ls -la $(SRC_DIR) || echo "$(SRC_DIR) not found!"
	@echo "\nChecking include directory:"
	@ls -la $(INCLUDE_DIR) || echo "$(INCLUDE_DIR) not found!"
	@echo "\nChecking libft directory:"
	@ls -la $(LIBFT_DIR) || echo "$(LIBFT_DIR) not found!"
	@echo "\nChecking headers:"
	@for header in $(HEADERS); do \
		if [ -f $$header ]; then \
			echo "$$header exists\033[0m"; \
		else \
			echo "$$header does not exist\033[0m"; \
		fi \
	done

.PHONY: all clean fclean re mk_objdir libft check
