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
		printf("%d has taken a fork", philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%d has taken a fork", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%d has taken a fork", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%d has taken a fork", philo->id);
	}
// PASO 2: ¡Comer! (Esto te faltaba)
    // Ahora que tiene AMBOS tenedores, el filósofo come.
    
    // 2a. Notificar que está comiendo
    printf("%d está comiendo\n", philo->id);
    
    // 2b. Actualizar su hora de última comida
    // ¿Qué variable de t_philo actualizarías?
    // ¿Y con qué función de utils.c?
    // Pista: philo->... = get_time_in_ms();
    
    // 2c. Dormir el tiempo de comida
    // ¿Qué función de utils.c usarías?
    // ¿Y qué variable de programa le pasarías?
    // Pista: precise_sleep(philo->program->...);
    
    // 2d. (Opcional, pero necesario para el arg[5])
    // Incrementar el contador de comidas
    // philo->meals_eaten++;

    // PASO 3: Soltar tenedores (¡MUY IMPORTANTE!)
    // Después de comer, ¡debe soltarlos para que otros coman!
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    // (El orden de soltar da igual)
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
	printf("Filósofo %d ha entrado en la simulación.\n", philo->id);

	return (NULL); // Los hilos deben devolver algo, NULL está bien para nosotros.
}