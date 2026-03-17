#include "minishell.h"
/*
// Necesitas pasar envp del sistema
int main(int ac, char **av, char **envp)
{
	t_shell shell;

	(void)ac;
	(void)av;
	char *test[2];

	test[0] = "patatas";
	test[1] = "src";
	// Inicializa correctamente con el entorno del sistema
	init_shell_state(&shell, envp);

	printf("Antes de pwd:\n");
	printf("PWD en env: %s\n", get_env_var("PWD", &shell));
	// Llama a builtin_pwd
	builtin_pwd(NULL, &shell);
	builtin_cd(test, &shell);
	printf("Después de pwd:\n");
	printf("PWD en env: %s\n", get_env_var("PWD", &shell));
	builtin_pwd(NULL, &shell);

	// Limpia
	free_resources(&shell);
	return (0);
}
*/