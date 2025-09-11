/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:55:02 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/11 13:55:13 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

// Mueve el primer nodo de la pila al final de la misma.
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return;
	first = *stack;
	last = ft_stack_last(*stack);
	*stack = first->next;
	first->next = NULL;
	last->next = first;
}

void	ra(t_stack **stack_a, int print)
{
	rotate(stack_a);
	if (print)
		write(1, "ra\n", 3);
}

void	rb(t_stack **stack_b, int print)
{
	rotate(stack_b);
	if (print)
		write(1, "rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
	rotate(stack_a);
	rotate(stack_b);
	if (print)
		write(1, "rr\n", 3);
}