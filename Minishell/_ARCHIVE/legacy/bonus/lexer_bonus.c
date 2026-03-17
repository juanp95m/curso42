#include "minishell_bonus.h"

/**
 * @brief Versión bonus del lexer: Itera sobre la cadena de entrada y la divide en tokens,
 *        reconociendo operadores lógicos (&&, ||) y paréntesis ((), así como los ya existentes.
 *
 * Proceso:
 * 1.  Similar al lexer base, pero con reconocimiento adicional para:
 *     -   `&&` como token `AND_IF`.
 *     -   `||` como token `OR_IF`.
 *     -   `(` como token `L_PAREN`.
 *     -   `)` como token `R_PAREN`.
 * 2.  Mantiene el manejo de comillas, redirecciones y palabras.
 *
 * @param line La línea de comandos introducida por el usuario.
 *             Ej: "ls -l && (grep main || echo 'error')"
 *
 * @return Una lista enlazada de tokens (`t_token`). Los tokens de operadores lógicos
 *         y paréntesis pueden tener un campo `type` expandido si se usa `t_tokentype_bonus`
 *         o se remapean al `t_tokentype` base. Para simplicidad, se asume que
 *         se puede adaptar el `t_token` base o se crearán nuevos tipos.
 *         Ej: [WORD:"ls"] -> [WORD:"-l"] -> [AND_IF] -> [L_PAREN] -> [WORD:"grep"] -> ...
 */
t_token	*lexer_bonus(char *line)
{
	(void)line;
	// TODO: Implementar un lexer que reconozca los tokens base
	//       (WORD, PIPE, REDIRECT_IN, REDIRECT_OUT, APPEND, HEREDOC)
	//       y además los nuevos para el bonus: AND_IF, OR_IF, L_PAREN, R_PAREN.
	//       Asegúrate de que la precedencia de reconocimiento sea correcta
	//       (p. ej., `&&` antes de `&`, `||` antes de `|`).

	return (NULL);
}
