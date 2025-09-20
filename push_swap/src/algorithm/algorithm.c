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

// --- FUNCIÓN 'sort_stack' ACTUALIZADA ---
void	sort_stack(t_stack **stack_a)
{
	t_stack	*stack_b;
	int		size;

	stack_b = NULL;
	size = ft_stack_size(*stack_a);
	if (is_sorted(*stack_a))
		return;
	if (size == 2)
		sa(stack_a, 1);
	else if (size == 3)
		sort_three(stack_a);
	else if (size <= 5)
		sort_five(stack_a, &stack_b);
	else
		radix_sort(stack_a, &stack_b);
}




