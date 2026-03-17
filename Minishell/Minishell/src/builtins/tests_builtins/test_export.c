#include "minishell.h"
/*
// Este main actúa como un simulador directo del comando export
int main(int ac, char **av, char **envp)
{
	t_shell shell;

	// 1. Inicializamos la shell con el entorno real de tu Linux
	// (Asegúrate de que init_shell_state funcione correctamente)
	init_shell_state(&shell, envp);

	// 2. Truco para simular los argumentos:
	// Cuando ejecutes "./test A=1", av será {"./test", "A=1", NULL}
	// Cambiamos av[0] a "export" para que tu función reciba 
	// {"export", "A=1", NULL}
	av[0] = "export";

	printf("\n🔵 --- EJECUTANDO TU BUILTIN_EXPORT ---\n");
	int ret = builtin_export(av, &shell);
	printf("🔵 --- RETORNO: %d ---\n", ret);

	// 3. Si agregaste variables, imprimimos la lista completa para verificar
	if (ac > 1) 
	{
		printf("\n🔎 --- VERIFICACIÓN (LISTA ACTUALIZADA) ---\n");
		char *args_verificacion[] = {"export", NULL};
		printf("\n🔎 --- VERIFICACIÓN (EXPORT) ---\n");
		builtin_export(args_verificacion, &shell);
		printf("\n🔎 --- VERIFICACIÓN (ENV) ---\n");
		builtin_env(args_verificacion, &shell);
		// ./minishell TEST=hola | grep TEST
	}
	free_resources(&shell);
	return (0);
}
*/