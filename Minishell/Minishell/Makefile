# **************************************************************************** #
#                                CONFIGURATION                                 #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP
SRC_DIR	:= src
SRC_BUILT = builtins
OBJ_DIR      := obj
OBJ_DIR_BONUS := obj_bonus

# **************************************************************************** #
#                                HEADERS                                       #
# **************************************************************************** #

HEADERS	:= -I ./includes

# **************************************************************************** #
#                                LIBRARIES                                     #
# **************************************************************************** #

LIBFT     := lib/libft/libft.a
LREAD      += -lreadline
BONUS_FLAG := .bonus

# **************************************************************************** #
#                                OBJECTS                                       #
# **************************************************************************** #

SRC_BUILTINS = builtin_cd.c \
builtin_echo.c \
builtin_env.c \
builtin_exit.c \
builtin_export.c \
builtin_pwd.c \
builtin_unset.c

SRC_FILES = debuger.c \
env.c \
error.c \
env_utils.c \
env_utils_paths.c \
executor.c \
executor_builtins.c \
executor_utils.c \
executor_utils_pipe.c \
expander.c \
expander_utils.c \
free_simple.c \
free_complex.c \
lexer.c \
lexer_handler.c \
lexer_utils.c \
lexer_utils2.c \
check_syntax.c \
main.c \
main_loop.c \
main_interactive.c \
parser.c \
parser_redirections.c \
parser_utils.c \
quote_removal.c \
signals.c \
heredoc_signals.c \
heredoc_utils.c \
heredoc.c \
struct_creation.c \
struct_enum_handler.c \
struct_initializer.c \
token_splitter.c

BONUS_EXTRA = wildcards_bonus.c \
wildcards_utils_bonus.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJS += $(addprefix $(OBJ_DIR)/$(SRC_BUILT)/, $(SRC_BUILTINS:.c=.o))
OBJS_BONUS := $(patsubst $(OBJ_DIR)/%,$(OBJ_DIR_BONUS)/%,$(OBJS))
OBJS_BONUS := $(subst $(OBJ_DIR_BONUS)/parser.o,$(OBJ_DIR_BONUS)/parser_bonus.o,$(OBJS_BONUS))
OBJS_BONUS += $(addprefix $(OBJ_DIR_BONUS)/, $(BONUS_EXTRA:.c=.o))


# **************************************************************************** #
#                                COLORS                                        #
# **************************************************************************** #
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
RED		= \033[0;31m
PURPLE	= \033[0;35m
RESET	= \033[0m
BOLD	= \033[1m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): CFLAGS += -DBONUS=0
$(NAME): $(OBJS) | $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LREAD) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Build complete: $(NAME)$(RESET)"

# **************************************************************************** #
#                                EXT LIBRARIES                                 #
# **************************************************************************** #
$(LIBFT):
	@echo "$(PURPLE)$(BOLD)Building Libs$(RESET)\n"
	@$(MAKE) -C lib/libft

# **************************************************************************** #
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

-include $(OBJS:.o=.d)

bonus: CFLAGS += -DBONUS=1
bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(OBJS_BONUS) | $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) $(LREAD) -o $(NAME)
	@touch $(BONUS_FLAG)
	@echo "$(GREEN)$(BOLD)Bonus build complete: $(NAME)$(RESET)"

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

-include $(OBJS_BONUS:.o=.d)

libft: $(LIBFT)

clean_bonus:
	@rm -rf $(OBJ_DIR_BONUS)
	@rm -f $(BONUS_FLAG)
	@echo "$(RED)Cleaned bonus objects$(RESET)"

re_bonus: clean_bonus bonus

# **************************************************************************** #
#                                CLEANING RULES                                #
# **************************************************************************** #
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C lib/libft clean
	@echo "$(RED)Cleaned objects$(RESET)"

fclean: clean clean_bonus
	@rm -f $(NAME)
	@$(MAKE) -C lib/libft fclean
	@echo "$(RED)Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re re_bonus clean_bonus libft
