#ifndef STRUCTS_H
# define STRUCTS_H

// -----------------------------------------------------------------------------
// DATA STRUCTURES
// -----------------------------------------------------------------------------

/**
 * @brief Represents an environment variable in a
 * linked list (key and value).
 * @param key "USER, PATH"
 * @param value "bin:/usr/sbin:"
 * @param next next variable
 */
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

/**
 * @brief Contains the entire state of the shell. Created at startup
 * and a pointer to it is passed through the main functions.
 * @param env_vars Copy of the environment to allow modification 
 * (`export`, `unset`).
 * @param env_list Linked list of environment variables
 * @param last_exit_code Value of `$?` updated after each command.
 */
typedef struct s_shell
{
	char				**env_vars;
	struct s_env		*env_list;
	int					last_exit_code;
	int					exit_requested;
	int					heredoc_count;
	pid_t				main_pid;
	struct s_token		*current_tokens;
	struct s_node		*current_ast;
}						t_shell;

typedef enum e_bool
{
	FALSE,
	TRUE,
	ERROR
}	t_bool;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

/**
 * @brief Enum for different types of token
 * @enum WORD	a.out, ls, -la
 * @enum EXTERNAL	any external executable (e.g. ls, cat, grep).
 * @enum OPERATOR	| < > << >>
 * @enum REDIRECT IN	<
 * @enum REDIRECT OUT	>
 * @enum APPEND	>>
 * @enum HEREDOC	<<
 * @enum AND	&&
 * @enum OR	||
 * @enum PIPE	|
 * @enum R_PAREN
 * @enum L_PAREN
 * @enum BUILTIN	cd, echo, env, exit, export, pwd, unset
 * @note ... flags for each builtin separated
 */
typedef enum e_tokentype
{
	WORD,
	EXTERNAL,
	OPERATOR,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	AND,
	OR,
	PIPE,
	R_PAREN,
	L_PAREN,
	BUILTIN,
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET,
}			t_tokentype;

/**
 * @brief Enum type for node types of the
 * AST (Abstract Syntax Tree)
 */
typedef enum e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD
}	t_node_type;

/**
 * @brief Represents a single token (a "word" or an "operator").
 * The Lexer generates a linked list of these structures.
 * @param value Value of the token as string
 * @param type Enum for type of token
 * @param next Next node
 * @param prev Previous node
 */
typedef struct s_token
{
	char				*value;
	t_tokentype			type;
	int					quote;
	int					expandable;
	int					nesting;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

/**
 * @brief Represents a simple command and its redirections.
 * The Parser generates a linked list of these structures.
 * @param args Command arguments (e.g. {"ls", "-l", NULL})
 * @param infile Name of the input file for <
 * @param heredoc_delimiters Array of delimiters for <<
 * @param heredoc_delim_count Number of heredoc delimiters
 * @param outfiles Array of output filenames for > and >>
 * @param append_modes Array of flags: 1 if >>, 0 if > (parallel to outfiles)
 * @param outfile_count Number of output redirections
 * @param next Next node command
 */
typedef struct s_command
{
	char				**args;
	char				*fullpath;
	t_tokentype			builtin_type;
	int					nesting;
	char				*infile;
	char				**heredoc_delimiters;
	int					heredoc_delim_count;
	int					heredoc_fd;
	char				**outfiles;
	int					*append_modes;
	int					outfile_count;
	struct s_command	*next;
}						t_command;

/**
 * @brief Represents a node in the execution tree.
 * It can be a simple command (leaf) or an operator (internal node).
 * The Parser generates this structure to represent the hierarchy of
 * commands and operators.
 * @param type Node type (PIPE, AND, OR, CMD)
 * @param left Left child (for operators)
 * @param right Right child (for operators)
 * @param cmd Pointer to the command (for CMD nodes)
 */
typedef struct s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	t_command		*cmd;
}					t_node;

#endif