/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:09:55 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/18 13:11:50 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos_meal_time(t_program *program, long long start_time)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		program->philos[i].last_meal_time = start_time;
		i++;
	}
}

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
			printf("Error: Failed to create \
the philosopher's thread %d\n", i + 1);
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
			printf("Error: Failed to create \
the philosopher's thread %d\n", i + 1);
			clean_and_destroy(program, program->num_philos);
			return (1);
		}
		i++;
	}
	return (0);
}
