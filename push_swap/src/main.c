/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:21:15 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/10 18:39:55 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// --- Función temporal para imprimir la pila ---
void    print_stack(t_stack *stack)
{
    printf("--- Contenido del Stack ---\n");
    if (!stack)
    {
        printf("(Vacío)\n");
        return;
    }
    while (stack)
    {
        printf("Valor: %d\n", stack->value);
        stack = stack->next;
    }
    printf("---------------------------\n");
}
#include "push_swap.h"

// Función para liberar la memoria del array creado por ft_split
static void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	char	**split_args;

	stack_a = NULL;
	if (argc < 2)
		return (0);
	// --- LÓGICA DE DETECCIÓN ---
	// Si argc es 2, podría ser un solo número o una cadena para splitear.
	if (argc == 2)
	{
		// Usamos ft_split para dividir la cadena por espacios.
		split_args = ft_split(argv[1], ' ');
		// La nueva función procesa el resultado del split.
		process_split_args(split_args, &stack_a);
		// ¡MUY IMPORTANTE! Liberamos la memoria usada por ft_split.
		free_split(split_args);
	}
	else // Si hay más de 2 argumentos, es el caso normal.
	{
		parse_arguments(argc, argv, &stack_a);
	}

	// El resto del programa sigue igual...
	if (stack_a)
		sort_stack(&stack_a);
	
	free_stack(&stack_a);
	return (0);
}