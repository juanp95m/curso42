#include "minishell.h"
/*
int main(int ac, char **av, char **envp)
{
	t_shell shell;
	char	*args_unset[] = {"unset", "USER", NULL};
	//char    *args_env[] = {"env", NULL};

	(void)ac;
	(void)av;

	// 1. Inicializamos la shell con el entorno real
	init_shell_state(&shell, envp);

	printf("\n--- ENTORNO INICIAL (Buscando USER) ---\n");
	// Imprimimos solo USER para no llenar la pantalla
	printf("USER = %s\n", get_env_var("USER", &shell));

	printf("\n--- EJECUTANDO UNSET USER ---\n");
	builtin_unset(args_unset, &shell);

	printf("\n--- ENTORNO FINAL (Buscando USER) ---\n");
	char *val = get_env_var("USER", &shell);
	if (val)
		printf("USER = %s (¡FALLO! Aún existe)\n", val);
	else
		printf("USER = (null) (¡ÉXITO! Ha sido borrada)\n");

	// Limpieza final para evitar leaks en Valgrind
	free_resources(&shell);

	return (0);
}
*/
