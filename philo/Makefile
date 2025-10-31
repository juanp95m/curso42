NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archivos fuente .c
SRCS = main.c \
parse.c \
inits.c \

# Archivos objeto .o
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re