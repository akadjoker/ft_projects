# Variáveis do Makefile
CC = gcc
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
CFLAGS = -g  -fPIC -fvisibility=hidden# a ideia é so ter as funcoes visiveis que sao EXPORT


INCLUDES = -Iinclude 
LDFLAGS = -shared
OBJDIR = obj
SRC_DIR = src

# Nomes das bibliotecas
DYNAMIC_NAME = libft_malloc_$(HOSTTYPE).so
LINK_NAME = libft_malloc.so


SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

# Debug info
$(info == Debug Information ==)
$(info Host Type: $(HOSTTYPE))
$(info Source files: $(SRC))
$(info Object files: $(OBJ))
$(info =====================)

# Regra principal
all: mk_objdir $(DYNAMIC_NAME)

# Criar diretório de objetos
mk_objdir:
	@mkdir -p $(OBJDIR)
	@echo "Created object directory: $(OBJDIR)"

# Compilar os objetos
$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[1;34m  Compiling [$< to $@]\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Criar a biblioteca dinâmica
$(DYNAMIC_NAME):  $(OBJ)
	@echo "\033[1;32mCreating shared library $(DYNAMIC_NAME)...\033[0m"
	$(CC) $(LDFLAGS) -o $(DYNAMIC_NAME) $(OBJ) $(LIBFT) -lpthread
	ln -sf $(DYNAMIC_NAME) $(LINK_NAME)
	@echo "\033[1;36m$(DYNAMIC_NAME) and $(LINK_NAME) are built!\033[0m"



# Limpeza dos objetos
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJDIR)
	@echo "\033[1;33mObject files removed.\033[0m"

# Limpeza completa
fclean: clean
	@echo "Removing shared and static libraries..."
	@rm -f $(DYNAMIC_NAME)  $(LINK_NAME)
	@echo "\033[1;33m$(DYNAMIC_NAME) and $(LINK_NAME) removed.\033[0m"


re: fclean all

ns:
	@echo "\033[1;32mListing static symbols...\033[0m"
	nm libft_malloc.so


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
