# Makefile para Minishell

Este documento contiene dos versiones del `Makefile` para este proyecto. Puedes copiar y pegar el contenido que necesites.

---

### Makefile (Parte Obligatoria)

Este `Makefile` compila únicamente los archivos de la parte obligatoria.

```makefile
# ------------------------------------------------------------------------------
#                                CONFIGURATION
# ------------------------------------------------------------------------------
NAME    := minishell
CC    := cc
CFLAGS    := -Wall -Wextra -Werror -MMD -MP
# Comenta la siguiente línea si no quieres usar -g (símbolos de debug)
CFLAGS    += -g
# Para readline en Linux:
# LIBS    += -lreadline
# Para readline en macOS:
# HEADERS += -I/path/to/your/homebrew/opt/readline/include
# LDFLAGS += -L/path/to/your/homebrew/opt/readline/lib

# ------------------------------------------------------------------------------
#                               DIRECTORIES & FILES
# ------------------------------------------------------------------------------
SRC_DIR := src
OBJ_DIR := obj

SRC_FILES = main.c \
            lexer.c \
            parser.c \
            executor.c \
            signals.c \
            env.c \
            builtins/builtin_cd.c \
            builtins/builtin_echo.c \
            builtins/builtin_pwd.c \
            builtins/builtin_export.c \
            builtins/builtin_unset.c \
            builtins/builtin_env.c \
            builtins/builtin_exit.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

-include $(OBJS:.o=.d)

# ------------------------------------------------------------------------------
#                                HEADERS & LIBRARIES
# ------------------------------------------------------------------------------
HEADERS    := -I ./includes -I ./lib/libft
LIBFT     := lib/libft/libft.a
LIBS      += $(LIBFT)

# ------------------------------------------------------------------------------
#                                COLORS
# ------------------------------------------------------------------------------
GREEN    = \033[0;32m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
RESET    = \033[0m
BOLD    = \033[1m

# ------------------------------------------------------------------------------
#                                   RULES
# ------------------------------------------------------------------------------
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
    @$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)
    @echo "$(GREEN)$(BOLD)Build complete: $(NAME)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    @mkdir -p $(dir $@)
    @$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(LIBFT):
    @echo "$(PURPLE)$(BOLD)Building Libft...$(RESET)"
    @$(MAKE) -s -C lib/libft

# ------------------------------------------------------------------------------
#                                CLEANING RULES
# ------------------------------------------------------------------------------
clean:
    @rm -rf $(OBJ_DIR)
    @$(MAKE) -s -C lib/libft clean
    @echo "$(BLUE)Cleaned objects$(RESET)"

fclean: clean
    @rm -f $(NAME)
    @$(MAKE) -s -C lib/libft fclean
    @echo "$(BLUE)Full clean done$(RESET)"

re: fclean all

.PHONY: all clean fclean re
```

---

### Makefile (Parte Bonus)

Este `Makefile` es más avanzado. Permite compilar la versión obligatoria con `make` y la versión bonus con `make bonus`. Los archivos objeto de cada versión se guardan en directorios separados (`obj` y `obj_bonus`) para no entrar en conflicto.

```makefile
# ------------------------------------------------------------------------------
#                                CONFIGURATION
# ------------------------------------------------------------------------------
NAME            := minishell
NAME_BONUS        := minishell_bonus
CC            := cc
CFLAGS            := -Wall -Wextra -Werror -MMD -MP
# Comenta la siguiente línea si no quieres usar -g (símbolos de debug)
CFLAGS            += -g
CFLAGS_BONUS    := $(CFLAGS) -D BONUS
# Para readline en Linux:
# LIBS            += -lreadline
# Para readline en macOS:
# HEADERS         += -I/path/to/your/homebrew/opt/readline/include
# LDFLAGS         += -L/path/to/your/homebrew/opt/readline/lib

# ------------------------------------------------------------------------------
#                               DIRECTORIES & FILES
# ------------------------------------------------------------------------------
SRC_DIR            := src
OBJ_DIR            := obj
OBJ_DIR_BONUS    := obj_bonus

# ---    Archivos para la parte obligatoria ---
SRC_FILES = main.c \
            lexer.c \
            parser.c \
            executor.c \
            signals.c \
            env.c \
            builtins/builtin_cd.c \
            builtins/builtin_echo.c \
            builtins/builtin_pwd.c \
            builtins/builtin_export.c \
            builtins/builtin_unset.c \
            builtins/builtin_env.c \
            builtins/builtin_exit.c

SRCS_MANDATORY := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS_MANDATORY := $(SRCS_MANDATORY:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ---    Archivos para la parte bonus ---
SRC_FILES_BONUS = main.c \
                  lexer_bonus.c \
                  parser_bonus.c \
                  executor_bonus.c \
                  expander_bonus.c \
                  signals.c \
                  env.c \
                  builtins/builtin_cd.c \
                  builtins/builtin_echo.c \
                  builtins/builtin_pwd.c \
                  builtins/builtin_export.c \
                  builtins/builtin_unset.c \
                  builtins/builtin_env.c \
                  builtins/builtin_exit.c

SRCS_BONUS := $(addprefix $(SRC_DIR)/, $(SRC_FILES_BONUS))
OBJS_BONUS := $(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)

-include $(OBJS_MANDATORY:.o=.d) $(OBJS_BONUS:.o=.d)

# ------------------------------------------------------------------------------
#                                HEADERS & LIBRARIES
# ------------------------------------------------------------------------------
HEADERS    := -I ./includes -I ./lib/libft
LIBFT     := lib/libft/libft.a
LIBS      += $(LIBFT)

# ------------------------------------------------------------------------------
#                                COLORS
# ------------------------------------------------------------------------------
GREEN    = \033[0;32m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
RESET    = \033[0m
BOLD    = \033[1m

# ------------------------------------------------------------------------------
#                                   RULES
# ------------------------------------------------------------------------------
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_MANDATORY)
    @$(CC) $(CFLAGS) $(OBJS_MANDATORY) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME)
    @echo "$(GREEN)$(BOLD)Build complete (mandatory): $(NAME)$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
    @$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) $(LIBS) $(LDFLAGS) $(HEADERS) -o $(NAME_BONUS)
    @echo "$(GREEN)$(BOLD)Build complete (bonus): $(NAME_BONUS)$(RESET)"

# ---    Reglas de compilación ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    @mkdir -p $(dir $@)
    @$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
    @mkdir -p $(dir $@)
    @$(CC) $(CFLAGS_BONUS) -c $< -o $@ $(HEADERS)

# ---    Libft ---
$(LIBFT):
    @echo "$(PURPLE)$(BOLD)Building Libft...$(RESET)"
    @$(MAKE) -s -C lib/libft

# ------------------------------------------------------------------------------
#                                CLEANING RULES
# ------------------------------------------------------------------------------
clean:
    @rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
    @$(MAKE) -s -C lib/libft clean
    @echo "$(BLUE)Cleaned objects$(RESET)"

fclean: clean
    @rm -f $(NAME) $(NAME_BONUS)
    @$(MAKE) -s -C lib/libft fclean
    @echo "$(BLUE)Full clean done$(RESET)"

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
```