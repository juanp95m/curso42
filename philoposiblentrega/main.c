/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/18 13:17:38 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		printf("Error: creating boss threads in main");
		clean_and_destroy(&program, program.num_philos);
		return (1);
	}
	clean_and_destroy(&program, program.num_philos);
	return (0);
}
