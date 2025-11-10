/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/07 17:03:03 by jperez-m         ###   ########.fr       */
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

// Forward declaration para poder usar t_program en t_philo
typedef struct s_program t_program;

// La "ficha" de cada filósofo
typedef struct s_philo
{
	int				id;              // El número del filósofo (1 a N)
	pthread_t		thread;          // El identificador de su hilo
	long long		last_meal_time;  // Momento de su última comida
	int				meals_eaten;     // Contador de comidas
	pthread_mutex_t	*left_fork;      // Puntero al mutex del tenedor izquierdo
	pthread_mutex_t	*right_fork;     // Puntero al mutex del tenedor derecho
	t_program		*program;        // Puntero a la estructura principal
}	t_philo;

// La estructura principal que lo contiene todo
typedef struct s_program
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long long		start_time;
	t_philo			*philos;         // Array de filósofos
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	*forks;        // Array de mutex (tenedores)
	pthread_t		boss_thread;
}	t_program;


//utils.c
int 		allocate_memory(t_program *program);
void    	clean_and_destroy(t_program *program);
long long	get_time_in_ms(void);
void		precise_sleep(long long duration_ms);
void		free_philos_forks(t_program *program);
int 		is_one_philosopher(t_program *program);

//parse.c
int 		is_invalid_argument(int argc, char **argv);
long		ft_atolmax(const char *nptr);
int			ft_isspace(int c);
int			ft_isdigit(int c);

//inits.c
int 		init_program_struct(t_program *program, int argc, char **argv);
int 		init_forks(t_program *program);
void 		init_philos(t_program *program);
int 		init_all(t_program *program, int argc, char **argv);

//simulation
void		*philosopher_routine(void *arg);
void    	print_status(t_philo *philo, char *status_message);
void 		eating(t_philo *philo);
void 		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
#endif