/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/11/06 16:17:52 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Esta función lanzará todos los hilos
static int start_simulation(t_program *program)
{
	int i;

	i = 0;
	while (i < program->num_philos)
	{
		// pthread_create(puntero_al_hilo, atributos, funcion_rutina, argumento_para_la_rutina)
		if (pthread_create(&(program->philos[i].thread), NULL, &philosopher_routine, &program->philos[i]) != 0)
		{
			printf("Error: Fallo al crear un hilo.\n");
			return (1); // Error
		}
		i++;
	}
	return (0); // Éxito
}


int main(int argc, char **argv)
{
    t_program program;
    int       i;

    if (is_invalid_argument(argc, argv))
        return (1);
   // Inicializamos todo el programa (datos, memoria, mutex).
    // La propia función se encarga de la limpieza si algo sale mal.
    if (init_program(&program, argc, argv))
        return (1);
printf("Iniciando la simulación...\n");
	if (start_simulation(&program))
	{
		cleanup(&program); // Si falla la creación, limpiamos y salimos
		return (1);
	}

	// Esperamos a que todos los hilos terminen.
	// pthread_join es como el director esperando a que cada actor termine su escena
	// antes de bajar el telón.
	i = 0;
	while (i < program.num_philos)
	{
		pthread_join(program.philos[i].thread, NULL);
		i++;
	}
	
    cleanup(&program);
    return (0);
}
