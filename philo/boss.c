/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 17:06:55 by marvin            #+#    #+#             */
/*   Updated: 2025/11/11 21:04:37 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Esta función lee el valor de simulation_stop de forma segura (protegida por mutex)
int should_stop(t_program *program)
{
    int stop;
    
    pthread_mutex_lock(&program->stop_mutex);
    stop = program->simulation_stop;
    pthread_mutex_unlock(&program->stop_mutex);
    return (stop);
}

//Poner simulation_stop a 1 de forma segura (con mutex)
void set_stop(t_program *program)
{
    pthread_mutex_lock(&program->stop_mutex);
    program->simulation_stop = 1;
    pthread_mutex_unlock(&program->stop_mutex);
}
//Lee el valor de last_meal_time de un filósofo específico de forma segura
long long get_last_meal(t_philo *philo) // se le pasa t_philo porque etsamos diciendo: dame la ultima comida de este filosofo
{
    long long last_meal;
    
    pthread_mutex_lock(&philo->program->meal_mutex);
    last_meal = philo->last_meal_time;
    pthread_mutex_unlock(&philo->program->meal_mutex);
    return (last_meal);
}

