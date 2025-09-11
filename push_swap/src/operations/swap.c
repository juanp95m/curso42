/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:54:28 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/11 13:54:31 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/operations/swap.c
#include "push_swap.h"

// Intercambia los dos primeros elementos del stack a.
static void	swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next)
		return;
	first = *stack;
	second = (*stack)->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	sa(t_stack **stack_a, int print)
{
	swap(stack_a);
	if (print)
		write(1, "sa\n", 3);
}

void	sb(t_stack **stack_b, int print)
{
	swap(stack_b);
	if (print)
		write(1, "sb\n", 3);
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	swap(stack_a);
	swap(stack_b);
	if (print)
		write(1, "ss\n", 3);
}