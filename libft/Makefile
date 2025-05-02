# Nombre de la biblioteca que generamos
NAME = libft.a

# Compilador y flags de compilación
CC = cc
CFLAGS = -Wall -Wextra -Werror 

# Fuentes y objetos
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_strlen.c ft_bzero.c ft_toupper.c ft_tolower.c ft_memcpy.c ft_memmove.c ft_strncmp.c ft_strchr.c ft_strrchr.c
OBJS = $(SRC:.c=.o)

# Regla por defecto construye la biblioteca
all: $(NAME)

# como crear libft.a a partir de los .o
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Regla generica para compilar cada .c en .o

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@
	
# Elimina los .c y .o
clean:
	rm -f $(OBJS)

# Elimina los .o y la libreria
fclean: clean
	rm -f $(NAME)

# Vuelve a compilar desde cero
re: fclean all

# Marcar reglas que no corresponden a archivos
.PHONY: all clean fclean re
