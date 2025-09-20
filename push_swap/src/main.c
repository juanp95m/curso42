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
static void    print_stack(t_stack *stack)
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

int	main(int argc, char **argv)
{
	t_stack *stack_a;

	stack_a = NULL;
	if (argc < 2)
		return (0);

	// Un único flujo de parsing: cada argv[i] puede contener uno o varios números
	parse_arguments(argc, argv, &stack_a);

	if (stack_a)
		sort_stack(&stack_a);

	free_stack(&stack_a);
	return (0);
}