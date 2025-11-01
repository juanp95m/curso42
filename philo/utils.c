/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:09:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/31 17:27:32 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Nueva función para liberar todos los recursos.
 * Destruye los mutex y libera la memoria de los arrays.
*/
void    cleanup(t_program *program)
{
    int i;

    i = 0;
    while (i < program->data.num_philos)
    {
        // Como 'program' aquí es un puntero, usamos '->'
        pthread_mutex_destroy(&program->forks[i]);
        i++;
    }
    free(program->philos);
    free(program->forks);
}

/*
 * Nueva función para reservar la memoria necesaria para los filósofos y los tenedores.
 * Usamos malloc para crear los arrays basados en el número de filósofos.
*/
int allocate_memory(t_program *program)
{
    // Reservamos memoria para el array de filósofos.
    program->philos = malloc(sizeof(t_philo) * program->data.num_philos);
    if (!program->philos) // Si malloc falla, devuelve NULL.
    {
        printf("Error: Malloc para filósofos ha fallado.\n");
        return (1); // Devolvemos 1 (error).
    }

    // Reservamos memoria para el array de tenedores (mutex).
    program->forks = malloc(sizeof(pthread_mutex_t) * program->data.num_philos);
    if (!program->forks)
    {
        printf("Error: Malloc para tenedores ha fallado.\n");
        // ¡Importante! Si esto falla, debemos liberar la memoria que ya habíamos reservado.
        free(program->philos);
        return (1); // Devolvemos 1 (error).
    }
    return (0); // Devolvemos 0 (éxito).
}