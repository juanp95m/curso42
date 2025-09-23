# Project name
NAME = push_swap

# Tools
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -I./libft
RM      = rm -f

# Directories
LIBFT_DIR   = ./libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
SRC_DIR     = src

# Sources
SRC_FILES = main.c\
algorithm.c \
algorithm_utils.c \
free_stack.c \
parsing.c \
parsing_utils.c \
push.c \
radix_sort.c \
reverse_rotate.c \
rotate.c \
small_sort.c \
stack_utils.c \
swap.c \
validation.c \

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Objects
OBJS = $(SRCS:.c=.o)

# Link against libft
LDFLAGS = -L$(LIBFT_DIR) -lft

# Default target
all: $(NAME)

# Executable linking
$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully"

# Build libft
$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

.SUFFIXES: .c .o

# Generic compilation rule
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Include automatically generated dependencies
-include $(OBJS:.o=.d)

# Clean objects
clean:
	@$(RM) $(OBJS) $(OBJS:.o)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	echo $(OBJS)

# Full clean
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

# Recompile from scratch
re: fclean all

.PHONY: all clean fclean re