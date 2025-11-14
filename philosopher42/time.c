/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:33:34 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 17:14:51 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long duration_ms)
{
	long long	start_time;
	long long	elapsed;

	start_time = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start_time;
		if (elapsed >= duration_ms)
			break ;
		if ((duration_ms - elapsed) > 10)
			usleep(1000);
		else
			usleep(100);
	}
}
