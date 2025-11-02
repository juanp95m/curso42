/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/31 17:48:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * Este es el "guion" que cada filósofo (hilo) ejecutará.
 * Recibe un argumento genérico (void *), que sabemos que es un puntero
 * a la estructura del filósofo (t_philo).
*/
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	// Convertimos el puntero genérico de vuelta a un puntero de t_philo
	philo = (t_philo *)arg;

	// Por ahora, solo imprimimos un mensaje para saber que el hilo se creó.
	// Usamos philo->id para saber qué filósofo está hablando.
	printf("Filósofo %d ha entrado en la simulación.\n", philo->id);

	return (NULL); // Los hilos deben devolver algo, NULL está bien para nosotros.
}