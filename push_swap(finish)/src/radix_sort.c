/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:35:29 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:26:48 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	assign_indexes(t_stack *stack)
{
	t_stack	*current;
	t_stack	*runner;
	int		index;

	current = stack;
	while (current)
	{
		index = 0;
		runner = stack;
		while (runner)
		{
			if (current->value > runner->value)
				index++;
			runner = runner->next;
		}
		current->index = index;
		current = current->next;
	}
}

void	radix_sort(t_stack **a, t_stack **b)
{
	int	i;
	int	j;
	int	size;
	int	max_bits;

	assign_indexes(*a);
	size = ft_stack_size(*a);
	max_bits = 0;
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	i = -1;
	while (++i < max_bits)
	{
		j = -1;
		while (++j < size)
		{
			if ((((*a)->index >> i) & 1) == 0)
				pb(a, b, 1);
			else
				ra(a, 1);
		}
		while (*b)
			pa(a, b, 1);
	}
}
