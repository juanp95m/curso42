/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:36:19 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:28:11 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_integer(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
		if (str[1] == '\0')
			return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicates(t_stack *stack)
{
	t_stack	*current;
	t_stack	*indexnode;

	current = stack;
	while (current)
	{
		indexnode = current->next;
		while (indexnode)
		{
			if (current->value == indexnode->value)
				return (1);
			indexnode = indexnode->next;
		}
		current = current->next;
	}
	return (0);
}
