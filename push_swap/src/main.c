/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:36:40 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/29 16:24:15 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	stack_a = NULL;
	if (argc < 2)
		return (0);
	parse_arguments(argc, argv, &stack_a);
	if (stack_a)
		sort_stack(&stack_a);
	free_stack(&stack_a);
	return (0);
}
