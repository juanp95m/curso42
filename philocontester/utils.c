/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:09:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/13 16:11:15 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_one_philosopher(t_program *program)
{
	program->start_time = get_time_in_ms();
	program->philos[0].last_meal_time = program->start_time;
	print_status(&program->philos[0], "has taken a fork");
	precise_sleep(program->time_to_die);
	print_status(&program->philos[0], "died");
	clean_and_destroy(program, program->num_philos);
	return (0);
}

void	free_philos_forks(t_program *program)
{
	if (program->philos)
		free(program->philos);
	if (program->forks)
		free(program->forks);
	program->philos = NULL;
	program->forks = NULL;
}

int	clean_and_destroy(t_program *program, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->printf_mutex);
	pthread_mutex_destroy(&program->meal_mutex);
	pthread_mutex_destroy(&program->stop_mutex);
	free_philos_forks(program);
	return (1);
}

int	allocate_memory(t_program *program)
{
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
	{
		printf("Error: Malloc para filósofos ha fallado.\n");
		return (1);
	}
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
	{
		printf("Error: Malloc para tenedores ha fallado.\n");
		free(program->philos);
		return (1);
	}
	return (0);
}
