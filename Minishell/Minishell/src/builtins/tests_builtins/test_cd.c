#include "minishell.h"

/*
// Utilidad para imprimir el estado actual y ver si cd funcionó
void debug_print_state(t_shell *shell, char *etiqueta)
{
	char buf[1024];

	printf("\n--- %s ---\n", etiqueta);
	
	// 1. Verificamos el directorio real del sistema
	if (getcwd(buf, sizeof(buf)))
		printf("Sistema getcwd(): %s\n", buf);
	else
		perror("getcwd");

	// 2. Verificamos las variables internas de nuestra shell
	printf("Shell env PWD:    %s\n", get_env_var("PWD", shell));
	printf("Shell env OLDPWD: %s\n", get_env_var("OLDPWD", shell));
	printf("---------------------------\n");
}

int main(int ac, char **av, char **envp)
{
	t_shell shell;

	// 1. Inicializar la shell con las variables de entorno reales
	// IMPORTANTE: Se pasa 'envp', no '*envp'
	init_shell_state(&shell, envp);

	debug_print_state(&shell, "ESTADO INICIAL");

	// 2. Llamar a builtin_cd
	// Pasamos 'av' directamente.
	// Si ejecutas: ./test_cd ..
	// av[0] = "./test_cd" (builtin_cd ignora el índice 0)
	// av[1] = ".."        (builtin_cd usa esto como destino)
	// av[2] = NULL
	
	printf("\nEjecutando builtin_cd...\n");
	if (ac > 1)
		builtin_cd(av, &shell);       // Prueba con argumentos: ./test_cd <ruta>
	else
	{
		// Prueba sin argumentos (debería ir a HOME)
		// Fabricamos un array manual porque av[1] es NULL aquí
		char *args[] = {"cd", NULL}; 
		builtin_cd(args, &shell);
	}

	debug_print_state(&shell, "ESTADO FINAL");
	free_resources(&shell);
	return (0);
}
*/