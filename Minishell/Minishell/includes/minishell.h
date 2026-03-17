#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "libft.h"
# include "structs.h"
# include <dirent.h>

extern int	g_signal_status;

// src/check_syntax.c
int			is_pipe_op(t_tokentype type);
int			is_redir(t_tokentype type);
int			is_operator(t_tokentype type);
char		*pipe_op_str(t_tokentype type);
int			check_middle_and_trailing(t_token *tokens, char *input);

// src/debuger.c
void		debug_print_tokens(t_token *head);
void		debug_print_commands(t_command *head);
void		debug_print_ast(t_node *node, int level);

// src/env.c
char		**dup_env_array(char **envp);
char		*get_env_var(char *name, t_shell *shell);
void		set_env_var(char *key, char *value, t_shell *shell);
char		**from_envlist_2_envp(t_env *env_list);

// src/error.c
void		exit_with_exec_error(char *cmd, t_shell *shell);
void		ms_perror(char *ctx, char *msg);
int			check_syntax_errors(t_token *tokens, char *input);
void		print_syntax_error(char *op, char *input);

// src/env_utils.c
int			ft_envsize(t_env *env);
char		*ft_getenv(t_env *env, char *key);
t_env		*ft_env_new(char *key, char *value);
void		ft_env_add_back(t_env **list, t_env *new_node);

// src/env_utils_paths.c
char		*find_command(char *cmd, t_shell *shell);
void		assign_fullpath_recursive(t_node *node, t_shell *shell);

// src/executor.c
int			exec_node_logic(t_node *node, t_shell *shell);
int			exec_node_pipe(t_node *node, t_shell *shell);
int			exec_node_cmd(t_node *node, t_shell *shell);
int			traverse_tree(t_node *node, t_shell *shell);

// src/executor_builtins.c
int			print_builtin_help(t_tokentype builtin_type);
int			exec_builtin_parent(t_command *cmd, t_shell *shell);

// src/executor_utils.c
int			handle_input_redirections(t_command *cmd);
int			handle_output_redirections(t_command *cmd);
int			setup_redirections(t_command *cmd);
void		exec_external_child(t_command *cmd, t_shell *shell);

// src/executor_utils_pipe.c
void		close_pipe(int pfd[2]);
void		wait_pipe(pid_t left, pid_t right, int *status);
int			open_fork(int pfd[2], int std, t_node *node, t_shell *shell);

// src/expander.c
char		*ft_strjoin_free(char *s1, char *s2);
t_token		*add_expansion_info(t_token *head);
char		*get_var_value(char *var_name, t_shell *shell);
t_token		*expand_dollars(t_shell *shell, t_token *head);

// src/expander_utils.c
char		*extract_var_segment(char *str, int *i, t_shell *shell);
int			has_expandable_dollar(char *str);
char		*handle_quote_char(char *str, int *i, int *q);
char		*extract_literal(char *str, int *i, int *q);

// src/free_complex.c
void		free_ast(t_node *node);
void		free_tokens(t_token *head);
void		cleanup_child_process(t_shell *shell);
void		free_shell(t_shell *shell);
void		free_single_cmd(t_command *cmd);

// src/free_simple.c
void		free_env_node(t_env *node);
void		free_array(char **arr);
void		free_env_list(t_env *env);
void		free_keyval(char *key, char *val);
void		free_env_error(char **envp, int i);

// src/heredoc.c
int			preprocess_heredocs(t_node *node, t_shell *shell);
int			get_heredoc_fd(t_command *cmd, t_shell *shell);
int			process_heredoc(char *delimiter, int heredoc_num, t_shell *shell);

// src/heredoc_signals.c
void		heredoc_sigint(int sig);
void		setup_heredoc_signals(void);
char		*generate_heredoc_name(int num);
void		write_heredoc_loop(int fd, char *delimiter);
void		heredoc_child_process(char *filename, char *delim, t_shell *shell);

// src/heredoc_utils.c
char		*read_line_raw(int fd);

// src/lexer.c
int			handle_word(char *line, int i, t_token **list);
t_token		*lexer(char *line);

// src/lexer_handler.c
int			skip_quotes(char *line, int i);
int			has_dollar(char *str);
int			is_dbl(char *str);
int			handle_operator(char *line, int i, t_token **list);

// src/lexer_utils.c
int			is_special_char(char c);
int			is_space(char c);
int			is_quote(char c);

// src/lexer_utils2.c
void		assign_parenthesis_depth(t_token *token);
int			is_empty_input(char *input);

// src/main.c
void		increment_shlvl(t_shell *shell);
void		create_basic_env_vars(t_shell *shell);
void		check_signal_status(t_shell *shell);
int			main(int ac, char **av, char **envp);

// src/main_loop.c
char		*get_user_input(char *ps1);
t_token		*process_tokens(t_token *tokens, t_shell *shell);
void		execute_command_tree(t_node *nodes, t_shell *shell);

// src/main_interactive.c
void		process_tokens_parser(t_token *tokens, t_node *nodes,\
			t_shell *shell);
void		process_input(char *input, t_shell *shell);
void		run_shell(t_shell *shell);

// src/parser.c  (mandatory) / src/parser_bonus.c (bonus)
t_node		*parse_simple_cmd(t_token **tokens);
t_node		*parse_pipe(t_token **tokens);
t_node		*parser(t_token *tokens);
t_node		*parse_expression(t_token **tokens);

// src/parser_redirections.c
int			parse_infile(t_command *command, t_token **tokens);
int			parse_outfile(t_command *command, t_token **tokens);
int			parse_heredoc(t_command *command, t_token **tokens);

// src/parser_utils.c
void		add_arg(t_command *command, t_token *token);
int			dispatch_redirections(t_command *cmd, t_token **tokens);
t_node		*handle_parenthesis(t_token **tokens);
int			check_syntax_errors(t_token *tokens, char *input);

// src/quote_removal.c
t_token		*remove_quotes_from_tokens(t_token *head);

// src/signals.c
void		handle_sigint(int sig);
void		setup_interactive_signals(void);
void		setup_ignore_signals(void);
void		setup_noninteractive_signals(void);
void		setup_child_signals(void);
int			handle_exit_status(int status);

// src/struct_creation.c
t_token		*create_new_token(char *value, int type);
void		add_token_back(t_token **head, t_token *new);

// src/struct_enum_handler.c
int			recon_builtin(char *str);
int			assign_token_type(char *str);

// src/struct_initializer.c
t_command	*create_cmd_node(void);
t_node		*create_ast_node(t_node_type type);
void		init_shell_state(t_shell *shell, char **envp);
void		create_envp_list(char **envp, t_shell *shell);

// src/token_splitter.c
t_token		*split_expanded_tokens(t_token *head);

// src/wildcards_bonus.c / src/wildcards_utils_bonus.c
# if BONUS

t_token		*expand_wildcards(t_token *head);
void		swap_nodes_value(t_token *a, t_token *b);
void		sort_matches(t_token *head);
# endif

// src/builtins/
int			builtin_cd(char **args, t_shell *shell);
int			builtin_echo(char **args, t_shell *shell);
int			is_valid_env_name(char *str);
int			builtin_env(char **args, t_shell *shell);
int			builtin_exit(char **args, t_shell *shell);
int			builtin_export(char **args, t_shell *shell);
int			builtin_pwd(char **args, t_shell *shell);
int			builtin_unset(char **args, t_shell *shell);

#endif
