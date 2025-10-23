# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/15 10:47:28 by jperez-m          #+#    #+#              #
#    Updated: 2025/10/23 17:13:31 by jperez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = fractol

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ilibft -IMLX42/include

# Libraries and linking flags
LDFLAGS = -L$(LIBFT_DIR) -lft -LMLX42/build -lmlx42
LIBS = -lglfw -ldl -lm -lpthread
LIBS_X11 = -lX11 -lXrandr -lXi -lXxf86vm -lXcursor

# Source and object files
SRCS = main.c \
render.c \
init.c \
hooks.c \
utils.c \
mandelbrot.c \
julia.c \
events.c \
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

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS) $(LIBS_X11)
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
