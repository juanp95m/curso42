# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 10:47:28 by jperez-m          #+#    #+#              #
#    Updated: 2025/10/28 17:24:17 by jperez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = fractol

# Variables
CC = cc
# MLX42 directory
MLX_DIR = MLX42

CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -I$(MLX_DIR)/include

# Libraries and linking flags
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR)/build -lmlx42
LIBS = -lglfw -lm -ldl -pthread

# Source and object files
SRCS = main.c \
render.c \
init.c \
hooks.c \
parse.c \
mandelbrot.c \
julia.c \
colors.c \
		
OBJS = $(SRCS:.c=.o)


# Libft path
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rule to compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Main rule
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/build/libmlx42.a
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "compiled successfully"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

# Build MLX42 if the static lib is missing
$(MLX_DIR)/build/libmlx42.a:
	@cmake -S $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null || true
	@cmake --build $(MLX_DIR)/build --config Release > /dev/null || true

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "Clean complete"

re: fclean all

.PHONY: all clean fclean re
