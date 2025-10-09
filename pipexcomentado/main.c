/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:46 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/08 11:14:47 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex data;

    if (argc != 5)
    {
        ft_printf("Uso: ./pipex infile cmd1 cmd2 outfile\n");
        return (1);
    }   
    init_pipex_data(&data, argv, envp);
    execute_processes(&data);
    cleanup(&data);
    return (0);
}
