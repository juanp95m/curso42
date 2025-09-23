/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:36:48 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/23 11:14:22 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	exit_with_cleanup(char **args, t_stack **stack_a)
{
	free_split_local(args);
	free_stack_and_error(stack_a);
}

void	process_split_args(char **args, t_stack **stack_a)
{
	int		i;
	long	nbr;
	t_stack	*new;

	i = 0;
	while (args[i])
	{
		if (!is_valid_integer(args[i]))
			exit_with_cleanup(args, stack_a);
		nbr = ft_atol(args[i]);
		if (nbr < INT_MIN || nbr > INT_MAX)
			exit_with_cleanup(args, stack_a);
		new = ft_stack_new((int)nbr);
		if (!new)
			exit_with_cleanup(args, stack_a);
		ft_stack_add_back(stack_a, new);
		i++;
	}
	if (has_duplicates(*stack_a))
		exit_with_cleanup(args, stack_a);
}

void	parse_arguments(int argc, char **argv, t_stack **stack_a)
{
	int		i;
	char	**split_args;

	i = 1;
	while (i < argc)
	{
		split_args = ft_split(argv[i], ' ');
		if (!split_args)
			free_stack_and_error(stack_a);
		process_split_args(split_args, stack_a);
		free_split_local(split_args);
		i++;
	}
}
