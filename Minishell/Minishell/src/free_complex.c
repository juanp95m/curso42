#include "minishell.h"

/**
 * @brief Recursively free the AST nodes and their associated command
 * structures.
 * @param node The root of the AST to free
 */
void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_CMD && node->cmd)
		free_single_cmd(node->cmd);
	free(node);
}

/**
 * @brief Free a linked list of tokens.
 * @param head The head of the token list to free
 */
void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

/**
 * @brief Clean up resources associated with a child process.
 * @param shell The shell state containing resources to clean up
 */
void	cleanup_child_process(t_shell *shell)
{
	if (shell->current_tokens)
		free_tokens(shell->current_tokens);
	if (shell->current_ast)
		free_ast(shell->current_ast);
	free_shell(shell);
	rl_clear_history();
}

/**
 * @brief Free all resources associated with the shell state, including the
 * environment list and array.
 * @param shell The shell state to free
 */
void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env_list)
		free_env_list(shell->env_list);
	if (shell->env_vars)
		free_array(shell->env_vars);
	shell->env_list = NULL;
	shell->env_vars = NULL;
}

/**
 * @brief Free a single command structure, including its arguments and
 * redirection information.
 * @param cmd The command structure to free
 */
void	free_single_cmd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->fullpath)
		free(cmd->fullpath);
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfiles)
		free_array(cmd->outfiles);
	if (cmd->append_modes)
		free(cmd->append_modes);
	if (cmd->heredoc_delimiters)
		free_array(cmd->heredoc_delimiters);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	free(cmd);
}
