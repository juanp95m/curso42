/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:09:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 17:17:09 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("Error:  Malloc for philosophers failed.\n");
		return (1);
	}
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
	{
		printf("Error: Malloc for forks failed.\n");
		free(program->philos);
		return (1);
	}
	return (0);
}

void	print_status(t_philo *philo, char *status_message)
{
	long long	time;

	if (should_stop(philo->program))
		return ;
	pthread_mutex_lock(&philo->program->printf_mutex);
	if (should_stop(philo->program))
	{
		pthread_mutex_unlock(&philo->program->printf_mutex);
		return ;
	}
	time = get_time_in_ms() - philo->program->start_time;
	printf("%lld %d %s\n", time, philo->id, status_message);
	pthread_mutex_unlock(&philo->program->printf_mutex);
}
