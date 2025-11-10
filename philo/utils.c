/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:09:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/06 16:06:21 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_one_philosopher(t_program *program)
{
    program->start_time = get_time_in_ms();
    program->philos[0].last_meal_time = program->start_time;
    print_status(&program->philos[0], "has taken a fork");
    precise_sleep(program->time_to_die);
    print_status(&program->philos[0], "died");
    clean_and_destroy(program);
    return (0);
}

void    free_philos_forks(t_program *program)
{
    if (program->philos)
        free(program->philos);
    if (program->forks)
        free(program->forks);
    program->philos = NULL;
    program->forks = NULL;
}

/*
 * Devuelve el tiempo actual en milisegundos.
 * 'gettimeofday' nos da el tiempo en segundos y microsegundos.
 * Nosotros lo convertimos todo a un único número en milisegundos.
*/
long long	get_time_in_ms(void)
{
	struct timeval	tv;

	// Obtenemos el tiempo actual
	gettimeofday(&tv, NULL);
	
	// Convertimos los segundos a milisegundos (tv_sec * 1000)
	// Convertimos los microsegundos a milisegundos (tv_usec / 1000)
	// Los sumamos para tener el total de milisegundos desde "el inicio de los tiempos".
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
 * Nueva función para "dormir" de forma más precisa.
 * Evita el "oversleeping" de usleep comprobando la hora en un bucle.
*/
void	precise_sleep(long long duration_ms)
{
	long long	start_time;

	// Obtenemos la hora de inicio
	start_time = get_time_in_ms();

	// Bucle: Mientras el tiempo actual MENOS el inicio sea MENOR que la duración
	while ((get_time_in_ms() - start_time) < duration_ms)
	{
		// Dormimos en intervalos muy pequeños (ej. 100 microsegundos)
		// Esto evita que el bucle consuma el 100% de la CPU ("busy-waiting"),
		// pero nos permite despertar frecuentemente para comprobar la hora.
		usleep(100);
	}
}

/*
 * Nueva función para liberar todos los recursos.
 * Destruye los mutex y libera la memoria de los arrays.
*/
void    clean_and_destroy(t_program *program)
{
    int i;

    i = 0;
    while (i < program->num_philos)
    {
        // Como 'program' aquí es un puntero, usamos '->'
        pthread_mutex_destroy(&program->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&program->printf_mutex);
    free_philos_forks(program);
}

/*
 * Nueva función para reservar la memoria necesaria para los filósofos y los tenedores.
 * Usamos malloc para crear los arrays basados en el número de filósofos.
*/
int allocate_memory(t_program *program)
{
    // Reservamos memoria para el array de filósofos.
    program->philos = malloc(sizeof(t_philo) * program->num_philos);
    if (!program->philos) // Si malloc falla, devuelve NULL.
    {
        printf("Error: Malloc para filósofos ha fallado.\n");
        return (1); // Devolvemos 1 (error).
    }

    // Reservamos memoria para el array de tenedores (mutex).
    program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
    if (!program->forks)
    {
        printf("Error: Malloc para tenedores ha fallado.\n");
        // ¡Importante! Si esto falla, debemos liberar la memoria que ya habíamos reservado.
        free(program->philos);
        return (1); // Devolvemos 1 (error).
    }
    return (0); // Devolvemos 0 (éxito).
}