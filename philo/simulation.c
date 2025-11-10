/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/07 19:37:05 by jperez-m         ###   ########.fr       */
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
    // 2b. Actualizar su hora de última comida
	philo->last_meal_time = get_time_in_ms();

    // 2c. Dormir el tiempo de comida
    precise_sleep(philo->program->time_to_eat);
    
    // 2d. (Opcional, pero necesario para el arg[5])
    // Incrementar el contador de comidas
    philo->meals_eaten++;

    // PASO 3: Soltar tenedores (¡MUY IMPORTANTE!)
    // Después de comer, ¡debe soltarlos para que otros coman!
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    // (El orden de soltar da igual)
}

void sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
    precise_sleep(philo->program->time_to_sleep);
}
void	thinking(t_philo *philo)
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

	// Convertimos el puntero genérico de vuelta a un puntero de t_philo
	philo = (t_philo *)arg;

	// Por ahora, solo imprimimos un mensaje para saber que el hilo se creó.
	// Usamos philo->id para saber qué filósofo está hablando.
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}

	return (NULL); // Los hilos deben devolver algo, NULL está bien para nosotros.
}

/*
 * Imprime un mensaje de estado de forma segura (protegido por mutex)
 * y con el formato de timestamp requerido.
*/
void    print_status(t_philo *philo, char *status_message)
{
    long long   timestamp;

    // 1. Bloquear el mutex de impresión
    pthread_mutex_lock(&philo->program->printf_mutex);

    // 2. Calcular el timestamp (Tiempo actual - Tiempo de inicio)
    // Usamos las funciones que ya tienes
    timestamp = get_time_in_ms() - philo->program->start_time;

    // 3. Imprimir el mensaje con el formato del subject
    printf("%lld %d %s\n", timestamp, philo->id, status_message);

    // 4. Desbloquear el mutex
    pthread_mutex_unlock(&philo->program->printf_mutex);
}