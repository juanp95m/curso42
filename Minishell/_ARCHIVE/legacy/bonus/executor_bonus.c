#include "minishell_bonus.h"

/**
 * @brief Versión bonus del executor: Ejecuta un Árbol de Sintaxis Abstracta (AST).
 *
 * Proceso:
 * 1.  Recorre el AST de forma recursiva.
 * 2.  Para nodos `NODE_COMMAND`:
 *     -   Expande los wildcards (`*`) usando `expand_wildcards()`.
 *     -   Comprueba si es un built-in o un comando externo.
 *     -   Si es un built-in que modifica el estado de la shell (`cd`, `export`, `unset`, `exit`),
 *         lo ejecuta directamente en el proceso padre.
 *     -   En otros casos, `fork()` un proceso hijo, configura redirecciones/pipes
 *         y ejecuta el comando (`execve` o built-in).
 * 3.  Para nodos `NODE_PIPE`:
 *     -   Ejecuta el lado izquierdo y el derecho, conectando su entrada/salida con tuberías.
 * 4.  Para nodos `NODE_AND` (`&&`):
 *     -   Ejecuta el lado izquierdo. Si el código de salida es 0, ejecuta el lado derecho.
 * 5.  Para nodos `NODE_OR` (`||`):
 *     -   Ejecuta el lado izquierdo. Si el código de salida NO es 0, ejecuta el lado derecho.
 * 6.  Para nodos `NODE_SUBSHELL` (`()`):
 *     -   `fork()` un proceso hijo.
 *     -   En el hijo, ejecuta recursivamente el sub-árbol del `NODE_SUBSHELL`.
 *     -   El padre espera al hijo y captura su código de salida.
 *
 * @param ast La raíz del Árbol de Sintaxis Abstracta.
 * @param shell El estado de la shell.
 * @return El código de salida del último comando/operación ejecutado.
 */
int	executor_bonus(t_ast_node *ast, t_shell *shell)
{
	(void)ast;
	(void)shell;
	if (!ast)
		return (0);

	// TODO: Implementar la lógica de ejecución recursiva del AST.
	//       - Usar un switch-case o if/else if para manejar los `t_ast_node_type`.
	//       - Para NODE_COMMAND:
	//           - Llamar a `expand_wildcards(ast->command)`.
	//           - Determinar si es built-in o externo.
	//           - Gestionar `fork`, pipes, redirecciones, `execve`.
	//       - Para NODE_PIPE, NODE_AND, NODE_OR:
	//           - Ejecutar recursivamente `ast->left` y `ast->right` según la lógica.
	//       - Para NODE_SUBSHELL:
	//           - Crear un `fork`.
	//           - En el hijo, ejecutar recursivamente `ast->left`.
	//           - En el padre, esperar al hijo.

	// TODO: Actualizar `shell->last_exit_code` con el resultado.
	return (0);
}
