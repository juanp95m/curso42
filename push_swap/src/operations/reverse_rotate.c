/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:55:20 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/11 13:55:22 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/operations/reverse_rotate.c
#include "push_swap.h"

// Mueve el último nodo de la pila a la primera posición.
static void	reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*prev_last;

	if (!stack || !*stack || !(*stack)->next)
		return;
	last = *stack;
	prev_last = NULL;
	while (last->next)
	{
		prev_last = last;
		last = last->next;
	}
	prev_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	rra(t_stack **stack_a, int print)
{
	reverse_rotate(stack_a);
	if (print)
		write(1, "rra\n", 4);
}

void	rrb(t_stack **stack_b, int print)
{
	reverse_rotate(stack_b);
	if (print)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	if (print)
		write(1, "rrr\n", 4);
}