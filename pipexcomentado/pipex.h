/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:37:51 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/08 13:53:56 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h> // fork
# include <sys/types.h> // pid_t, size_t, ssize_t
# include <sys/wait.h> // wait y waitpid
# include <stdio.h> // perror(), printf, NULL
# include <stdlib.h> // malloc, free y exit
# include <fcntl.h>  // Para open
# include "libft.h"
# include "ft_printf.h"

typedef struct s_pipex
{
    int     infile_fd;
    int     outfile_fd;
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;

    char    *cmd1_path; // Ruta completa a cmd1 (ej: /bin/ls)
    char    **cmd1_args; // Array de argumentos para cmd1 (ej: {"ls", "-l", NULL})

    char    *cmd2_path;
    char    **cmd2_args;

    char    **envp;      // Puntero al envp original

} t_pipex;

// Funciones principales
void    init_pipex_data(t_pipex *data, char **argv, char **envp);
void    execute_child_one(t_pipex data);
void    execute_child_two(t_pipex data);

// Funciones auxiliares
char    *find_command_path(char *cmd, char **envp);
void    perror_and_exit(char *msg);
void    free_and_exit(t_pipex *data);
void    execute_processes(t_pipex *data);
void    cleanup(t_pipex *data);
void    free_split(char **array);
void    command_not_found(const char *cmd_label, const char *cmd);
void    close_opened_files(t_pipex *data);

#endif