NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archivos fuente .c
SRCS = main.c \
parse.c \
inits.c \
utils.c \
simulation.c \
helpersboss.c \
boss.c \

# Archivos objeto .o
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -o $(NAME)
	@echo "$(NAME) Compiled successfully"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "Clean completed"

re: fclean all

.PHONY: all clean fclean re