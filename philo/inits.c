/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:58:04 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/31 17:47:30 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
 * Función para inicializar nuestra estructura `t_data` con los valores
 * que nos pasan por la terminal. `atoi` convierte texto ("123") a número (123).
*/
int init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	
    // Si tenemos el 5º argumento, lo guardamos. Si no, lo marcamos con -1.
	if (argc == 6)
		data->num_meals = atoi(argv[5]);
	else
		data->num_meals = -1;
	return (1);
}
