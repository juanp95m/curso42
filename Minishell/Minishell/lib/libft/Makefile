# **************************************************************************** #
#                            STANDARDIZED MAKEFILE                               #
# **************************************************************************** #

NAME    := libft.a            # Change this to ft_printf.a or gnl.a as needed
AR      := ar rcs
CC      := cc
RM      := rm -f
RMD     := rm -rf

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := ../../includes

CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR)


SRC_FILES := ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_strndup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_gnl_utils.c \
ft_gnl.c

SRC      := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS     := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# ================= Colors ===================
GREEN       = \033[0;32m
BLUE        = \033[0;34m
YELLOW      = \033[1;33m
RED         = \033[0;31m
RESET       = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
ITALIC      = \033[3m

# **************************************************************************** #
#                                  RULES                                       #
# **************************************************************************** #

all: $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
# 	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating archive $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RMD) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Full clean: removing archive...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
