/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:58:04 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 17:13:43 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_program_struct(t_program *program, int argc, char **argv)
{
	program->num_philos = ft_atolmax(argv[1]);
	program->time_to_die = ft_atolmax(argv[2]);
	program->time_to_eat = ft_atolmax(argv[3]);
	program->time_to_sleep = ft_atolmax(argv[4]);
	if (argc == 6)
		program->num_meals = ft_atolmax(argv[5]);
	else
		program->num_meals = -1;
	return (0);
}

int	init_forks(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			printf("Error: Fallo al inicializar un mutex.\n");
			return (clean_and_destroy(program, i));
		}
		i++;
	}
	return (0);
}

int	init_shared_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->printf_mutex, NULL) != 0)
	{
		printf("Error: Fallo al inicializar print_mutex\n");
		return (1);
	}
	if (pthread_mutex_init(&program->stop_mutex, NULL) != 0)
	{
		printf("Error: Fallo al inicializar stop_mutex\n");
		pthread_mutex_destroy(&program->printf_mutex);
		return (1);
	}
	if (pthread_mutex_init(&program->meal_mutex, NULL) != 0)
	{
		printf("Error: Fallo al inicializar meal_mutex\n");
		pthread_mutex_destroy(&program->printf_mutex);
		pthread_mutex_destroy(&program->stop_mutex);
		return (1);
	}
	program->simulation_stop = 0;
	return (0);
}

void	init_philos(t_program *program)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < program->num_philos)
	{
		philo = &program->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->last_meal_time = 0;
		philo->program = program;
		philo->left_fork = &program->forks[i];
		philo->right_fork = &program->forks[(i + 1) % program->num_philos];
		i++;
	}
}

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
