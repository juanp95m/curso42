/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:38:01 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/03 23:08:27 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Resolución de rutas de comandos:
 - get_path_variable: devuelve el valor de PATH (sin el prefijo "PATH=")
 - check_paths: concatena directorios de PATH con el comando y prueba X_OK
 - find_command_path: coordina la búsqueda y libera recursos auxiliares
*/

//solo busca y devuelve la línea PATH=... de envp
// Busca la variable PATH en envp y devuelve el puntero al valor tras "PATH="
static char *get_path_variable(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
            return (envp[i] + 5); // Devuelve el puntero justo después de "PATH="
        i++;
    }
    return (NULL);
}

// Recorre cada ruta de PATH, construye candidato y devuelve la primera ejecutable
static char *check_paths(char **all_paths, char *command)
{
    char    *temp_path;
    char    *full_path;
    int     i;

    i = 0;
    while (all_paths[i])
    {
        // Une el directorio con una "/"
        temp_path = ft_strjoin(all_paths[i], "/");
        if (!temp_path)
            return (NULL); // Protección por si falla malloc
        // Une lo anterior con el nombre del comando
        full_path = ft_strjoin(temp_path, command);
        free(temp_path); // Liberamos la string temporal
        if (!full_path)
            return (NULL);
        // Si la ruta es válida y ejecutable, la hemos encontrado
        if (access(full_path, X_OK) == 0)
            return (full_path);
            
        free(full_path); // Si no, la liberamos y seguimos
        i++;
    }
    return (NULL); // No se encontró en ninguna ruta
}

// Orquesta la búsqueda de la ruta ejecutable a partir del nombre del comando
char *find_command_path(char *command, char **envp)
{
    char    *path_variable;
    char    **all_paths;
    char    *executable_path;

    // 1. Obtiene la variable PATH del entorno
    path_variable = get_path_variable(envp);
    if (!path_variable)
        return (NULL); // No existe la variable PATH

    // 2. Divide la variable en un array de strings
    printf("path = %s\n", path_variable);
    all_paths = ft_split(path_variable, ':');
    if (!all_paths)
        return (NULL); // Fallo de malloc en ft_split

    // 3. Llama a la función trabajadora para que busque
    executable_path = check_paths(all_paths, command);
    printf("ubicacion = %s\n", executable_path);

    // 4. Libera el array de rutas que ya no necesitamos
    free_split(all_paths); // (Tu función para liberar el array 2D)

    // 5. Devuelve el resultado (la ruta encontrada o NULL)
    return (executable_path);
}
