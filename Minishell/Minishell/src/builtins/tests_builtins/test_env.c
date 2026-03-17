#include "minishell.h"
/*
int main(int ac, char **av, char **envp)
{
	t_shell shell;

	init_shell_state(&shell, envp);
	printf("--- INICIO DE PRUEBA ENV ---\n");

	if (ac > 1) 
	{
		// Si hay argumentos reales (ej: ./minishell hola), pasamos 'av'.
		// av[1] será "hola".
		builtin_env(av, &shell);
	}
	else
	{
		// Si no hay argumentos (ej: ./minishell), pasamos un array limpio para 
		// que env funcione.
		char *no_args[] = {"env", NULL};
		builtin_env(no_args, &shell);
	}

	printf("--- FIN DE PRUEBA ENV ---\n");
	free_resources(&shell);
	return (0);
}
*/