/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/31 17:48:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>  // Para printf
# include <stdlib.h> // Para atoi y exit
# include <unistd.h> // Para write
# include <limits.h> 
# include <pthread.h>    // Para hilos y mutex
# include <sys/time.h>   // Para gettimeofday

/*
 * Estructura para almacenar todos los datos de entrada de la simulación.
 * La usaremos para pasar toda la información de forma ordenada.
*/
typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}	t_data;

// La "ficha" de cada filósofo
typedef struct s_philo
{
	int				id;              // El número del filósofo (1 a N)
	pthread_t		thread;          // El identificador de su hilo
	long long		last_meal_time;  // Momento de su última comida
	int				meals_eaten;     // Contador de comidas
	pthread_mutex_t	*left_fork;      // Puntero al mutex del tenedor izquierdo
	pthread_mutex_t	*right_fork;     // Puntero al mutex del tenedor derecho
	t_data			*data;           // Puntero a la data general
}	t_philo;

// La estructura principal que lo contiene todo
typedef struct s_program
{
	t_data			data;
	t_philo			*philos;         // Array de filósofos
	pthread_mutex_t	*forks;          // Array de mutex (tenedores)
}	t_program;

//utils.c
int 	allocate_memory(t_program *program);
void    cleanup(t_program *program);

//parse.c
int 	is_invalid_argument(int argc, char **argv);
long	ft_atolmax(const char *nptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);

//inits.c
int 	init_data(t_data *data, int argc, char **argv);
int 	init_forks(t_program *program);
int 	init_program(t_program *program, int argc, char **argv);
void 	init_philos(t_program *program);

//simulation
void	*philosopher_routine(void *arg);
#endif