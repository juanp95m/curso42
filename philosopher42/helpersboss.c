/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpersboss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:26:12 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/13 16:25:31 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_program *program)
{
	int	stop;

	pthread_mutex_lock(&program->stop_mutex);
	stop = program->simulation_stop;
	pthread_mutex_unlock(&program->stop_mutex);
	return (stop);
}

void	set_stop(t_program *program)
{
	pthread_mutex_lock(&program->stop_mutex);
	program->simulation_stop = 1;
	pthread_mutex_unlock(&program->stop_mutex);
}

long long	get_last_meal(t_philo *philo)
{
	long long	last_meal;

	pthread_mutex_lock(&philo->program->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->program->meal_mutex);
	return (last_meal);
}

int	get_meals_eaten(t_philo *philo)
{
	int	meals;

	pthread_mutex_lock(&philo->program->meal_mutex);
	meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->program->meal_mutex);
	return (meals);
}
