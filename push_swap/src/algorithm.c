/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:05:58 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/17 19:50:20 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// --- 1. Función para comprobar si la pila ya está ordenada ---
// Recorre la pila y devuelve 1 si está ordenada, 0 si no.
static int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0); // No está ordenada
		stack = stack->next;
	}
	return (1); // Está ordenada
}

// --- 2. Algoritmos para casos pequeños ---

// Ordena una pila de 3 elementos.
// Identifica el caso específico y aplica la combinación óptima de movimientos.
static void	sort_three(t_stack **a)
{
	int	first;
	int	second;
	int	third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && second < third && first < third)
		sa(a, 1);
	else if (first > second && second > third)
	{
		sa(a, 1);
		rra(a, 1);
	}
	else if (first > second && second < third && first > third)
		ra(a, 1);
	else if (first < second && second > third && first < third)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (first < second && second > third && first > third)
		rra(a, 1);
}

// --- 3. La función "directora" del algoritmo ---
// Decide qué algoritmo usar según el tamaño de la pila.
void	sort_stack(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		size;

	stack_b = NULL;
	size = ft_stack_size(*stack_a);
	// Si la pila ya está ordenada, no hacemos nada.
	if (is_sorted(*stack_a))
		return;
	// Decide qué especialista llamar.
	if (size == 2)
		sa(stack_a, 1);
	else if (size == 3)
		sort_three(stack_a);
	// else if (size <= 5)
	//	sort_five(stack_a, &stack_b); // Lo haremos después
	// else
	// 	sort_large(stack_a, &stack_b); // El algoritmo Radix, para el final
}




