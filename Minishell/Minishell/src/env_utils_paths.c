#include "minishell.h"

/**
 * @brief Helper function to iterate through specific paths
 * Tries to join the path with the command and tests access
 * @return The valid full path or NULL
 */
static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Resolves the full path of a command
 * Checks if cmd is already a path, or searches inside PATH env var
 * @param cmd The command name (e.g., "ls")
 * @param shell Shell structure containing environment variables
 * @return Malocated string with absolute path or NULL
 */
char	*find_command(char *cmd, t_shell *shell)
{
	char	*path_var;
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_var = get_env_var("PATH", shell);
	if (!path_var)
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_array(paths);
	return (result);
}

/**
 * @brief Recursively assigns full paths to command nodes in the AST
 * @param node Pointer to the current AST node
 * @param shell Pointer to the shell context for environment variables
 */
void	assign_fullpath_recursive(t_node *node, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD && node->cmd)
	{
		if (node->cmd->args && node->cmd->args[0])
			node->cmd->fullpath = find_command(node->cmd->args[0], shell);
	}
	else
	{
		assign_fullpath_recursive(node->left, shell);
		assign_fullpath_recursive(node->right, shell);
	}
}
