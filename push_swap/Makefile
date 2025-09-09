# Makefile

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source directories
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
OPS_DIR = $(SRC_DIR)/operations

# Source files (.c)
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/algorithm.c \
       $(UTILS_DIR)/stack_utils1.c \
       $(UTILS_DIR)/stack_utils2.c \
       $(OPS_DIR)/push.c \
       $(OPS_DIR)/swap.c \
       $(OPS_DIR)/rotate.c \
       $(OPS_DIR)/reverse_rotate.c

OBJS = $(SRCS:.c=.o)

# Main rule
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# clean and compilation rule
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re