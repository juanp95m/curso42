/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/13 16:32:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->program->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meal_mutex);
	precise_sleep(philo->program->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->program->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	long long	time_to_think;

	print_status(philo, "is thinking");
	if (philo->program->num_philos % 2 != 0)
	{
		time_to_think = (philo->program->time_to_eat * 2)
			- philo->program->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		if (time_to_think > 600)
			time_to_think = 200;
		if (time_to_think > 0)
			usleep(time_to_think * 1000);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!should_stop(philo->program))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *status_message)
{
	long long	time;

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
