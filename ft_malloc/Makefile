# Variáveis do Makefile
CC = gcc
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
CFLAGS = -Wall -Wextra -Werror -fPIC -fvisibility=hidden# a ideia é so ter as funcoes visiveis que sao EXPORT


INCLUDES = -Iinclude -Ilibft/include
LDFLAGS = -shared
OBJDIR = obj
SRC_DIR = src

# Nomes das bibliotecas
DYNAMIC_NAME = libft_malloc_$(HOSTTYPE).so
STATIC_NAME = libft_malloc.a
LINK_NAME = libft_malloc.so

# Diretórios e arquivos
LIBFT = libft/libft.a
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# Debug info
$(info == Debug Information ==)
$(info Host Type: $(HOSTTYPE))
$(info Source files: $(SRC))
$(info Object files: $(OBJ))
$(info =====================)

# Regra principal
all: mk_objdir  $(STATIC_NAME) $(DYNAMIC_NAME)

# Criar diretório de objetos
mk_objdir:
	@mkdir -p $(OBJDIR)
	@echo "Created object directory: $(OBJDIR)"

# Compilar os objetos
$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[1;34m  Compiling [$< to $@]\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Criar a biblioteca dinâmica
$(DYNAMIC_NAME): $(LIBFT) $(OBJ)
	@echo "\033[1;32mCreating shared library $(DYNAMIC_NAME)...\033[0m"
	$(CC) $(LDFLAGS) -o $(DYNAMIC_NAME) $(OBJ) $(LIBFT)
	ln -sf $(DYNAMIC_NAME) $(LINK_NAME)
	@echo "\033[1;36m$(DYNAMIC_NAME) and $(LINK_NAME) are built!\033[0m"

# Criar a biblioteca estática
$(STATIC_NAME): $(OBJ)
	@echo "\033[1;32mCreating static library $(STATIC_NAME)...\033[0m"
	@ar rcs $(STATIC_NAME) $(OBJ)
	@echo "\033[1;36m$(STATIC_NAME) is built!\033[0m"

# Compilar a libft
$(LIBFT):
	@make -C libft

# Limpeza dos objetos
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@make -C libft clean
	@echo "\033[1;33mObject files removed.\033[0m"

# Limpeza completa
fclean: clean
	@echo "Removing shared and static libraries..."
	@rm -f $(DYNAMIC_NAME) $(STATIC_NAME) $(LINK_NAME)
	@make -C libft fclean
	@echo "\033[1;33m$(DYNAMIC_NAME), $(STATIC_NAME), and $(LINK_NAME) removed.\033[0m"


re: fclean all

ns:
	@echo "\033[1;32mListing static symbols...\033[0m"
	nm libft_malloc.so

na:
	@echo "\033[1;32mListing shared symbols...\033[0m"
	nm libft_malloc.a


# Verificar estrutura do projeto
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

.PHONY: all clean fclean re mk_objdir check
