# Nombre del ejecutable final
NAME = push_swap

# Compilador y flags (incluimos la ruta a las cabeceras de libft)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft

# Directorios de las librerías y fuentes
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
OPS_DIR = $(SRC_DIR)/operations

# Lista de todos tus archivos .c del proyecto
SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/algorithm.c \
	$(UTILS_DIR)/stack_utils.c \
	$(UTILS_DIR)/free_stack.c

# Genera la lista de archivos objeto (.o) a partir de los .c
OBJS = $(SRCS:.c=.o)

# Flags para el enlazador (linker) - le dice dónde encontrar libft
LDFLAGS = -L$(LIBFT_DIR) -lft

# Regla principal: depende del ejecutable
all: $(NAME)

# Regla para crear el ejecutable: depende de los .o y de la libft
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Regla para crear la libft: entra en su directorio y ejecuta su propio make
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Regla genérica para compilar cualquier .c en un .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Elimina solo los archivos objeto del proyecto
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean # También limpia los objetos de libft

# Elimina todo: objetos, el ejecutable y la libft.a
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean # También hace fclean en libft

# Recompila todo desde cero
re: fclean all

.PHONY: all clean fclean re