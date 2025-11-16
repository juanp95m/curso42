/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:19:56 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 16:21:11 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher_threads(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&philosopher_routine, &program->philos[i]) != 0)
		{
			printf("Error: Fail to create the philosopher's thread %d\n", i + 1);
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

int	join_all_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
		{
			printf("Error: fail to create the philosopher's thread %d\n", i + 1);
			clean_and_destroy(program, program->num_philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_program *program)
{
	int	i;

	program->start_time = get_time_in_ms();
	init_philos_meal_time(program, program->start_time);
	if (create_philosopher_threads(program))
		return (1);
	if (pthread_create(&program->boss_thread, NULL, boss_routine, program))
	{
		printf("Error: creating boss threads");
		i = 0;
		while (i < program->num_philos)
		{
			pthread_join(program->philos[i].thread, NULL);
			i++;
		}
		clean_and_destroy(program, program->num_philos);
		return (1);
	}
	return (0);
}
