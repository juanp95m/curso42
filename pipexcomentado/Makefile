NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./libft -I./printf
LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

SRCS = main.c\
setup.c\
processes.c\
utils.c\
utilsclean.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully"

$(LIBFT):
	@make -s -C libft

$(PRINTF):
	@make -s -C printf

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -f $(OBJS)
	@make -s -C libft clean
	@make -s -C printf clean

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@rm -f $(NAME)
	@make -s -C libft fclean
	@make -s -C printf fclean
	@echo "✅ Clean complete"  

re: fclean all

.PHONY: all clean fclean re