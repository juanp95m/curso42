/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:35:45 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:25:00 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*node_to_push;

	if (!src || !*src)
		return ;
	node_to_push = *src;
	*src = node_to_push->next;
	node_to_push->next = *dest;
	*dest = node_to_push;
}

void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	push(stack_b, stack_a);
	if (print)
		write(1, "pa\n", 3);
}

void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	push(stack_a, stack_b);
	if (print)
		write(1, "pb\n", 3);
}
