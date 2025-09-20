###
# Makefile para push_swap (incluye automáticamente todas las fuentes)
###

# Nombre del ejecutable final
NAME = push_swap

# Herramientas
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I. -I./libft -MMD -MP
RM      = rm -f

# Directorios
LIBFT_DIR   = ./libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
SRC_DIR     = src
ALGO_DIR    = $(SRC_DIR)/algorithm
OPS_DIR     = $(SRC_DIR)/operations
PARS_DIR    = $(SRC_DIR)/parsing
UTILS_DIR   = $(SRC_DIR)/utils

# Fuentes (recogidas automáticamente de subcarpetas)
SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing.c \
	$(wildcard $(ALGO_DIR)/*.c) \
	$(wildcard $(OPS_DIR)/*.c) \
	$(wildcard $(PARS_DIR)/*.c) \
	$(wildcard $(UTILS_DIR)/*.c)

# Objetos
OBJS = $(SRCS:.c=.o)

# Enlazado contra libft
LDFLAGS = -L$(LIBFT_DIR) -lft

# Objetivo por defecto
all: $(NAME)

# Enlazado del ejecutable
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Construcción de libft
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Regla genérica de compilación
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Incluir dependencias generadas automáticamente
-include $(OBJS:.o=.d)

# Limpieza de objetos
clean:
	$(RM) $(OBJS) $(OBJS:.o=.d)
	$(MAKE) -C $(LIBFT_DIR) clean # Limpia también libft

# Limpieza total
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilar desde cero
re: fclean all

.PHONY: all clean fclean re