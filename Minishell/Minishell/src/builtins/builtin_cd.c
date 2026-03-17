#include "minishell.h"

/**
 * @brief Update the PWD and OLDPWD environment variables after a successful cd.
 * @param shell The shell state containing environment variables.
 * @param old_path The previous working directory
 * before the cd command was executed.
*/
static void	update_env_var(t_shell *shell, char *old_path)
{
	char	*new_path;

	new_path = getcwd(NULL, 0);
	if (new_path)
		set_env_var("PWD", new_path, shell);
	if (old_path)
		set_env_var("OLDPWD", old_path, shell);
	free(new_path);
}

/**
 * @brief Get and duplicate an env var, printing an error if not set.
 * @param var The environment variable name (e.g., "HOME", "OLDPWD").
 * @param shell The shell state containing environment variables.
 * @return A duplicated string of the variable's value, or NULL if not set.
 */
static char	*get_env_or_error(char *var, t_shell *shell)
{
	char	*val;

	val = get_env_var(var, shell);
	if (!val)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" not set", 2);
		return (NULL);
	}
	return (ft_strdup(val));
}

/**
 * @brief Get the target path for the cd command based on the argument.
 * @param arg The argument passed to cd (e.g., NULL, "-", or a specific path).
 * @param shell The shell state containing environment variables.
 * @return The target path to change to (always allocated), or NULL on error.
 */
static char	*get_cd_path(char *arg, t_shell *shell)
{
	char	*path;

	if (!arg || ft_strncmp(arg, "~", 2) == 0)
		return (get_env_or_error("HOME", shell));
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		path = get_env_or_error("OLDPWD", shell);
		if (path)
			ft_putendl_fd(path, 1);
		return (path);
	}
	if (ft_strncmp(arg, "~", 1) == 0)
	{
		path = get_env_or_error("HOME", shell);
		if (!path)
			return (NULL);
		return (ft_strjoin_free(path, &arg[1]));
	}
	return (ft_strdup(arg));
}

/**
 * @brief Handles errors for the cd command
 * @param mode Error mode (0 for chdir error, 1 for other errors)
 * @param path The path being changed to
 * @param old_pwd The previous working directory
 * @return 1 on error, 0 on success
 */
static int	cd_error(int mode, char *path, char *old_pwd)
{
	if (mode == 0)
		fprintf(stderr, "minishell: cd: %s: %s\n", path, strerror(errno));
	free(path);
	free(old_pwd);
	if (mode == 0)
		return (1);
	return (0);
}

/**
 * @brief Implements the cd builtin command
 * @param args Arguments passed to the cd command
 * @param shell The shell state
 * @return 0 on success, 1 on error
 */
int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*old_pwd;

	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd && get_env_var("PWD", shell))
		old_pwd = ft_strdup(get_env_var("PWD", shell));
	path = get_cd_path(args[1], shell);
	if (!path)
	{
		free(old_pwd);
		return (1);
	}
	if (chdir(path) != 0)
		return (cd_error(0, path, old_pwd));
	update_env_var(shell, old_pwd);
	return (cd_error(1, path, old_pwd));
}
