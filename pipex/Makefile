NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./libft
LIBFT = libft/libft.a  

SRCS = main.c\
setup.c\
processes.c\
utils.c\
utilsclean.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully"

$(LIBFT):
	@make -s -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -f $(OBJS)
	@make -s -C libft clean

fclean: clean
	@echo "🗑️  Removing $(NAME)..."
	@rm -f $(NAME)
	@make -s -C libft fclean
	@echo "✅ Clean complete"  

re: fclean all

.PHONY: all clean fclean re