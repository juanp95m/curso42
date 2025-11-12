/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/12 18:12:33 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philos_meal_time(t_program *program, long long start_time)
{
	int i;
	
	i = 0;
	while (i < program->num_philos)
	{
		program->philos[i].last_meal_time = start_time;
		i++;
	}
}

int create_philosopher_threads(t_program *program)
{
	int i;
	int j;
	
	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philosopher_routine, &program->philos[i]) != 0)
		{
			printf("Error: Fallo al crear el hilo del filosofo %d\n", i + 1);
			j = 0;
			while (j < i)
			{
				pthread_join(program->philos[j].thread, NULL);
				j++;
			}
			clean_and_destroy(program, program->num_philos);
			return (1);
		}
		i++;
	}
	return (0);
}
int join_all_threads(t_program *program)
{
	int	i;
	
	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
		{
			printf("Error: fallo al crear el hilo del filosofo %d\n", i + 1);
			clean_and_destroy(program, program->num_philos);
			return (1);
		}
		i++;
	}
	return (0);
}
int start_simulation(t_program *program)
{
	program->start_time = get_time_in_ms();
	
	init_philos_meal_time(program, program->start_time);
	if (create_philosopher_threads(program))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
    t_program program;

    if (is_invalid_argument(argc, argv))
        return (1);
    if (init_all(&program, argc, argv))
		return (1);
	if (program.num_philos == 1)
        return (is_one_philosopher(&program));
	if (start_simulation(&program) == 1)
		return (1);
	// Esperamos a que todos los hilos terminen.
	// pthread_join es como el director esperando a que cada actor termine su escena
	// antes de bajar el telón.
	if (join_all_threads(&program))
		return (1);
	clean_and_destroy(&program, program.num_philos);
    return (0);
}
