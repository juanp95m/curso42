/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 17:08:38 by jperez-m         ###   ########.fr       */
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

int	is_invalid_argument(int argc, char **argv)
{
	int	i;
	int	num;

	if (argc < 5 || argc > 6)
	{
		printf("invalid arguments number\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		num = ft_atolmax(argv[i]);
		if (num <= 0)
		{
			printf("arguments must be a integer number bigger than 0 \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_all(t_program *program, int argc, char **argv)
{
	if (init_program_struct(program, argc, argv))
		return (1);
	if (allocate_memory(program))
		return (1);
	if (init_forks(program))
	{
		free_philos_forks(program);
		return (1);
	}
	if (init_shared_mutexes(program))
	{
		clean_and_destroy(program, program->num_philos);
		return (1);
	}
	init_philos(program);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (is_invalid_argument(argc, argv))
		return (1);
	if (init_all(&program, argc, argv))
		return (1);
	if (program.num_philos == 1)
		return (is_one_philosopher(&program));
	if (start_simulation(&program) == 1)
		return (1);
	if (join_all_threads(&program))
		return (1);
	if (pthread_join(program.boss_thread, NULL))
	{
		printf("Error: crearing boss threads in main");
		clean_and_destroy(&program, program.num_philos);
		return (1);
	}
	clean_and_destroy(&program, program.num_philos);
	return (0);
}
