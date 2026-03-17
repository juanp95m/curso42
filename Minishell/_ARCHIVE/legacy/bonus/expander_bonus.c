#include "minishell_bonus.h"

/**
 * @brief Expande los caracteres wildcard '*' en los argumentos de un comando.
 *
 * Proceso:
 * 1.  Itera sobre el array `command->args`.
 * 2.  Si un argumento contiene el carácter `*`, lo interpreta como un patrón.
 * 3.  Busca en el sistema de archivos los nombres de archivo que coincidan con el patrón.
 *     (p. ej., para "*.c" en un directorio con "main.c", "utils.c", expandiría a
 *     "main.c", "utils.c").
 * 4.  Reemplaza el argumento original con la lista de nombres de archivo encontrados.
 *     -   Si no se encuentra ninguna coincidencia, el argumento original se mantiene
 *         sin cambios (comportamiento de bash).
 *     -   Esto puede implicar reasignar `command->args` a un nuevo array.
 *
 * @param command Puntero a la estructura `t_command` cuyos argumentos
 *                necesitan expansión de wildcards.
 */
void	expand_wildcards(t_command *command)
{
	// TODO: Iterar sobre `command->args`.
	
	// TODO: Para cada argumento, comprobar si contiene `*`.
	
	// TODO: Si contiene `*`:
	//       - Implementar la lógica para hacer "globbing" (buscar archivos que coincidan).
	//       - Esto puede requerir funciones auxiliares que lean el directorio actual
	//         y comparen nombres de archivos con el patrón.
	//       - Reemplazar el argumento con la lista expandida.
	//         Si el argumento era `src/*.c` y hay `src/a.c` y `src/b.c`,
	//         el argumento `src/*.c` se borraría y se añadirían `src/a.c` y `src/b.c`.
	//         Esto implica manejar la memoria del array `args`.
	
	(void)command; // Para evitar warnings de variable no usada.
}
