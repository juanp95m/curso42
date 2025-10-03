/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:46 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/03 20:04:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Flujo general del programa:
 1) Validar argumentos (argc == 5)
 2) init_pipex_data -> prepara fds, pipe y comandos
 3) execute_processes -> crea hijos y ejecuta cmd1 | cmd2
 4) cleanup -> libera memoria y cierra fds en el padre
*/

// Punto de entrada: valida inputs, inicializa, ejecuta y limpia
int main(int argc, char **argv, char **envp)
{
    t_pipex data;

    if (argc != 5)
    {
        write(2, "Uso: ./pipex infile cmd1 cmd2 outfile\n", 38);
        return (1);
    }
    
    // 1. Inicializa la estructura con todos los datos necesarios
    init_pipex_data(&data, argv, envp);

    // 2. Lanza los procesos hijos
    // (Esta función contendrá los forks y las llamadas a las funciones de los hijos)
    execute_processes(&data);

    // 3. Limpia y libera memoria (si es necesario)
    cleanup(&data);

    return (0);
}