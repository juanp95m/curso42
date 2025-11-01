/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/10/31 17:15:19 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_program program;

    if (parse_arguments(argc, argv))
    {
        printf("invalid arguments\n");
        return (1);
    }
   // Inicializamos todo el programa (datos, memoria, mutex).
    // La propia función se encarga de la limpieza si algo sale mal.
    if (init_program(&program, argc, argv))
        return (1);
    printf("¡Programa inicializado con éxito!\n");
    printf("¡%d filósofos y %d tenedores listos en la mesa!\n",
        program.data.num_philos, program.data.num_philos);
    // Al final, solo llamamos a nuestra función de limpieza.
    // Le pasamos la dirección de 'program' (&program) porque 'cleanup' espera un puntero.
    cleanup(&program);
    return (0);
}