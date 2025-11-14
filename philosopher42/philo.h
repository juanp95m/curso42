/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:11 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/14 17:16:18 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h> 
# include <pthread.h>
# include <sys/time.h>

typedef struct s_program	t_program;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_program		*program;
}	t_philo;

typedef struct s_program
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				simulation_stop;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	*forks;
	pthread_t		boss_thread;
}	t_program;

//utils.c
int			allocate_memory(t_program *program);
int			clean_and_destroy(t_program *program, int size);
void		free_philos_forks(t_program *program);

//time.c
long long	get_time_in_ms(void);
void		precise_sleep(long long duration_ms);

//parse.c
long		ft_atolmax(const char *nptr);
int			ft_isspace(int c);
int			ft_isdigit(int c);

//inits.c
int			init_program_struct(t_program *program, int argc, char **argv);
int			init_forks(t_program *program);
void		init_philos(t_program *program);
int			init_shared_mutexes(t_program *program);
void		init_philos_meal_time(t_program *program, long long start_time);

//simulation.c
void		*philosopher_routine(void *arg);
void		print_status(t_philo *philo, char *status_message);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

//boss.c
int			is_someone_died(t_program *program);
int			check_all_meals_completed(t_program *program);
void		*boss_routine(void *arg);

//helpersboss.c
int			should_stop(t_program *program);
void		set_stop(t_program *program);
long long	get_last_meal(t_philo *philo);
int			get_meals_eaten(t_philo *philo);

//thread_manager.c
int			create_philosopher_threads(t_program *program);
int			join_all_threads(t_program *program);
int			start_simulation(t_program *program);

//main.c
int			is_one_philosopher(t_program *program);
int			is_invalid_argument(int argc, char **argv);
int			init_all(t_program *program, int argc, char **argv);
#endif