SRCS =	src/main.c \
		src/actions.c \
		src/handles.c \
		src/malloc_free.c \
		src/mutex.c \
		src/parsing.c \
		src/utils.c \
		src/utils2.c \

NAME = philo

COMPRESS = ar rcs	

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

# Lista de arquivos .o correspondentes aos .c
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

# Regra para criar o executável a partir dos arquivos objeto e bibliotecas
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo $(NAME) ready!

# Regra para compilar arquivos objeto a partir de arquivos fonte, cria a pasta para o arq obj se nao existir
$(OBJ_DIR)/%.o: src/%.c | $(CREATE_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(CREATE_DIR):
	@mkdir -p $(OBJ_DIR)/src

clean:
	@$(RM) -r $(OBJ_DIR)  # Remove o diretório obj e seu conteúdo

fclean: clean
	@$(RM) $(NAME)  # Remove o executável

re: fclean all

.PHONY: all clean fclean re