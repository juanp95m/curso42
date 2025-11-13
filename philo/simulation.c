/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/13 13:11:38 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating(t_philo *philo)
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

void sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
    precise_sleep(philo->program->time_to_sleep);
}
void thinking(t_philo *philo)
{
    print_status(philo, "is thinking");
}
/*
 * Este es el "guion" que cada filósofo (hilo) ejecutará.
 * Recibe un argumento genérico (void *), que sabemos que es un puntero
 * a la estructura del filósofo (t_philo).
*/
void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!should_stop(philo->program))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}

	return (NULL);
}

/*
 * Imprime un mensaje de estado de forma segura (protegido por mutex)
 * y con el formato de time requerido.
*/
void    print_status(t_philo *philo, char *status_message)
{
    long long   time;

    // 1. Bloquear el mutex de impresión
    pthread_mutex_lock(&philo->program->printf_mutex);

    if (should_stop(philo->program))
    {
        pthread_mutex_unlock(&philo->program->printf_mutex);
        return;  
    }
    // 2. Calcular el time (Tiempo actual - Tiempo de inicio)
    // Usamos las funciones que ya tienes
    time = get_time_in_ms() - philo->program->start_time;

    // 3. Imprimir el mensaje con el formato del subject
    printf("%lld %d %s\n", time, philo->id, status_message);

    // 4. Desbloquear el mutex
    pthread_mutex_unlock(&philo->program->printf_mutex);
}