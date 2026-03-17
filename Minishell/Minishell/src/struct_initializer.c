#include "minishell.h"

/**
 * @brief Create a new command structure, initializing all fields to default 
 * values.
 * @return A pointer to the newly created command structure, or NULL on
 */
t_command	*create_cmd_node(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = ft_calloc(1024, sizeof(char *));
	new_cmd->fullpath = NULL;
	new_cmd->infile = NULL;
	new_cmd->heredoc_delimiters = NULL;
	new_cmd->heredoc_delim_count = 0;
	new_cmd->heredoc_fd = -1;
	new_cmd->outfiles = NULL;
	new_cmd->append_modes = NULL;
	new_cmd->outfile_count = 0;
	new_cmd->builtin_type = WORD;
	new_cmd->nesting = -1;
	new_cmd->next = NULL;
	return (new_cmd);
}

/**
 * @brief Create a new AST node with the specified type, initializing all fields
 * to default values.
 * @param type The type of the AST node (e.g. NODE_PIPE, NODE_CMD)
 * @return A pointer to the newly created AST node, or NULL on allocation 
 * failure
 */
t_node	*create_ast_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->cmd = NULL;
	return (node);
}

/**
 * @brief Initialize the shell state by setting up the environment variable 
 * list and array, and initializing other fields to default values.
 * @param shell The shell state structure to initialize
 * @param envp The environment variables passed to the shell (from main)
 */
void	init_shell_state(t_shell *shell, char **envp)
{
	shell->env_list = NULL;
	shell->last_exit_code = 0;
	shell->exit_requested = 0;
	shell->env_vars = dup_env_array(envp);
	shell->heredoc_count = 0;
	shell->main_pid = getpid();
	shell->current_tokens = NULL;
	shell->current_ast = NULL;
	if (!envp)
		return ;
	create_envp_list(envp, shell);
}

/**
 * @brief Create a linked list of environment variables from the envp array. 
 * This function parses each string in envp to separate the key and value, 
 * creates a new t_env node for each variable, and adds it to the shell's 
 * env_list.
 * @param envp The array of environment variable strings (e.g. "PATH=/usr/bin")
 * @param shell The shell state to which the environment variables will 
 * be added
 */
void	create_envp_list(char **envp, t_shell *shell)
{
	char	*eq_pos;
	t_env	*new_node;
	char	*val;
	char	*key;
	int		i;

	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			key = ft_substr(envp[i], 0, eq_pos - envp[i]);
			val = ft_strdup(eq_pos + 1);
			if (key && val)
			{
				new_node = ft_env_new(key, val);
				if (new_node)
					ft_env_add_back(&shell->env_list, new_node);
			}
			free_keyval(key, val);
		}
		i++;
	}
}
