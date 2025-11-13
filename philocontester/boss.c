/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:06:55 by marvin            #+#    #+#             */
/*   Updated: 2025/11/13 16:27:56 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_died(t_program *program)
{
	int			i;
	t_philo		*philo;
	long long	last_meal;
	long long	current_time;
	long long	time_since_meal;

	i = 0;
	while (i < program->num_philos)
	{
		philo = &program->philos[i];
		last_meal = get_last_meal(philo);
		current_time = get_time_in_ms();
		time_since_meal = current_time - last_meal;
		if (time_since_meal >= program->time_to_die)
		{
			print_status(philo, "died");
			set_stop(program);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_meals_completed(t_program *program)
{
	int		i;
	int		count;
	t_philo	*philo;
	int		meals;

	if (program->num_meals == -1)
		return (0);
	count = 0;
	i = 0;
	while (i < program->num_philos)
	{
		philo = &program->philos[i];
		meals = get_meals_eaten(philo);
		if (meals >= program->num_meals)
			count++;
		i++;
	}
	if (count == program->num_philos)
	{
		set_stop(program);
		return (1);
	}
	return (0);
}

void	*boss_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (!should_stop(program))
	{
		is_someone_died(program);
		check_all_meals_completed(program);
		usleep(1000);
	}
	return (NULL);
}
