/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:58:04 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/07 12:25:24 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_program_struct(t_program *program, int argc, char **argv)
{
	program->num_philos = ft_atolmax(argv[1]);
	program->time_to_die = ft_atolmax(argv[2]);
	program->time_to_eat = ft_atolmax(argv[3]);
	program->time_to_sleep = ft_atolmax(argv[4]);
	if (argc == 6)
		program->num_meals = ft_atolmax(argv[5]);
	else
		program->num_meals = -1;
    return (0);
}

/*
 * Nueva función para inicializar cada tenedor (mutex) en la mesa.
 * Recorremos el array de 'forks' e inicializamos un mutex para cada uno.
*/
int init_forks(t_program *program)
{
    int i;

    i = 0;
    while (i < program->num_philos)
    {
        // Inicializamos el mutex en la posición 'i'.
        if (pthread_mutex_init(&program->forks[i], NULL) != 0)
        {
            printf("Error: Fallo al inicializar un mutex.\n");
            // Aquí podríamos tener una limpieza más compleja si algo falla
            // a mitad de camino, pero por ahora es suficiente.
            return (1); // Devolvemos 1 (error).
        }
        i++;
    }
    return (0); // Devolvemos 0 (éxito).
}

int init_shared_mutexes(t_program *program)
{
    // Usamos & porque 'print_mutex' ES la struct (sin *)
    if (pthread_mutex_init(&program->printf_mutex, NULL) != 0)
    {
        printf("Error: Fallo al inicializar print_mutex\n");
        return (1);
    }
    // ... aquí podrías inicializar futuros mutex ...
    return (0);
}

/*
 * función para inicializar los datos de cada filósofo.
 * Asigna un ID a cada uno y les dice cuáles son sus tenedores izquierdo y derecho.
*/
void init_philos(t_program *program)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < program->num_philos)
    {
        philo = &program->philos[i]; // Un puntero temporal para que el código sea más legible
        
        philo->id = i + 1; // Los IDs van de 1 a N
        philo->meals_eaten = 0;
        philo->last_meal_time = 0;
        philo->program = program; // Damos a cada filósofo acceso a la estructura principal

        // Asignación de tenedores
        // Tenedor izquierdo: el que tiene el mismo índice que el filósofo.
        philo->left_fork = &program->forks[i];
        
        // Tenedor derecho: el del siguiente filósofo. Para el último, es el tenedor 0.
        // El operador módulo (%) hace esto de forma automática y elegante.
        philo->right_fork = &program->forks[(i + 1) % program->num_philos];
        
        i++;
    }
}

/*
 * Función maestra que orquesta toda la inicialización del programa.
 * Llama a cada paso de la inicialización en orden.
 * Si un paso falla, se encarga de limpiar la memoria de los pasos anteriores.
*/
int init_all(t_program *program, int argc, char **argv)
{
    // Paso 1: Inicializar los datos de configuración.
    if (init_program_struct(program, argc, argv))
        return (1);

    // Paso 2: Reservar la memoria.
    if (allocate_memory(program))
        return (1); // Si falla, no hay nada que limpiar.

    // Paso 3: Inicializar los mutex (tenedores).
    if (init_forks(program))
    {
        // Si ESTE paso falla, SÍ tenemos que limpiar la memoria del paso anterior.
        free_philos_forks(program);
        return (1);
    }
    if (init_shared_mutexes(program)) // Inicializa los mutex singulares
    {
        // ... (limpieza, incluyendo la destrucción de los forks ya creados) ...
        free_philos_forks(program);
        return (1);
    }
    // Paso 4: Inicializar los datos de cada filósofo.
    init_philos(program); // No devuelve error, así que no necesita un if.
    // Si todos los pasos fueron exitosos:
    return (0);
}
