#include "minishell.h"

/**
 * @brief Implements the 'pwd' built-in command, which prints the current 
 * working directory. It uses the getcwd function to retrieve the current 
 * directory path and prints it to the standard output. If there is an error 
 * retrieving the current directory, it prints an error message to the standard 
 * error and returns a non-zero exit code.
 * @param args The arguments passed to the pwd command (not used).
 * @param shell The shell instance (not used).
 * @return 0 on success, 1 on failure.
 */
int	builtin_pwd(char **args, t_shell *shell)
{
	char	*path;
	char	*pwd_path;

	(void)args;
	path = getcwd(NULL, 0);
	if (!path)
	{
		pwd_path = get_env_var("PWD", shell);
		if (!pwd_path)
		{
			ms_perror("pwd", strerror(errno));
			return (1);
		}
		ft_putendl_fd(pwd_path, 1);
		return (0);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
