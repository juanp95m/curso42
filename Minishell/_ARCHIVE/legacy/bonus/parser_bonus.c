#include "minishell_bonus.h"

/**
 * @brief Versión bonus del parser: Construye un Árbol de Sintaxis Abstracta 
 *        (AST)a partir de una lista de tokens, manejando operadores lógicos y 
 *        subshells.
 *
 * Proceso:
 * 1.  No construye una lista de `t_command`, sino un árbol de `t_ast_node`.
 * 2.  Debe manejar la precedencia de operadores:
 *     -   Los paréntesis `()` tienen la mayor precedencia.
 *     -   Los pipes `|` tienen más precedencia que `&&` y `||`.
 *     -   `&&` y `||` tienen la menor precedencia.
 * 3.  Cuando encuentra un `L_PAREN`, el parser recursivamente procesa los tokens
 *     dentro hasta encontrar un `R_PAREN`, formando un nodo `NODE_SUBSHELL`.
 * 4.  Los comandos simples (tokens `WORD` y redirecciones) se agrupan en un
 *     `t_command` y se convierten en nodos `NODE_COMMAND` hoja del AST.
 *
 * @param tokens La lista enlazada de tokens del lexer_bonus.
 *
 * @return La raíz del Árbol de Sintaxis Abstracta (`t_ast_node`).
 *         Ej: Para "ls -l && (grep main | wc)", el output sería un árbol con
 *         un nodo `NODE_AND` en la raíz, un `NODE_COMMAND` a la izquierda
 *         (para "ls -l") y un `NODE_SUBSHELL` a la derecha. Dentro del
 *         `NODE_SUBSHELL`, habría un árbol (o sub-lista de comandos si el parser
 *         interno de subshells sigue siendo el base) para "grep main | wc".
 */
t_ast_node	*parser_bonus(t_token *tokens)
{
	(void)tokens;
	// TODO: Implementar un parser recursivo descendente o similar que construya un AST.
	//       Las funciones auxiliares para manejar diferentes niveles de precedencia
	//       serán muy útiles (p. ej., `parse_command()`, `parse_pipe()`, `parse_and_or()`).

	// TODO: Crear nodos `NODE_COMMAND` para comandos simples.
	// TODO: Crear nodos `NODE_PIPE`, `NODE_AND`, `NODE_OR` para los operadores.
	// TODO: Crear nodos `NODE_SUBSHELL` para los comandos entre paréntesis.

	// TODO: Devolver la raíz del AST.
	return (NULL);
}
