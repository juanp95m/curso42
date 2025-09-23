/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:35:37 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/22 15:24:14 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **a)
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

void	sort_five(t_stack **a, t_stack **b)
{
	int	min_val;
	int	pos;
	int	size;

	while (ft_stack_size(*a) > 3)
	{
		min_val = find_min_value(*a);
		pos = find_node_position(*a, min_val);
		size = ft_stack_size(*a);
		if (pos <= size / 2)
		{
			while ((*a)->value != min_val)
				ra(a, 1);
		}
		else
		{
			while ((*a)->value != min_val)
				rra(a, 1);
		}
		pb(a, b, 1);
	}
	sort_three(a);
	while (*b)
		pa(a, b, 1);
}
