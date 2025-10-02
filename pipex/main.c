/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:46 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/02 19:11:27 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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