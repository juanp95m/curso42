# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 10:47:28 by jperez-m          #+#    #+#              #
#    Updated: 2025/10/15 14:10:37 by jperez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME = fractol

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -IMLX42/include

# Archivos fuente y objeto
SRCS = main.c \
render.c \
		
OBJS = $(SRCS:.c=.o)


# Ruta de libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regla para compilar archivos objeto
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Regla principal
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -LMLX42/build -lmlx42 -lglfw -ldl -lm -lX11 -lpthread -lXrandr -lXi -lXxf86vm -lXcursor
	@echo "compiled successfully"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "Clean complete"

re: fclean all

.PHONY: all clean fclean re
