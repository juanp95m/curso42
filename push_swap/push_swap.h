/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:37:01 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/29 14:46:22 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include "libft.h"

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// src/algorithm/algorithm.c
void	sort_stack(t_stack **stack_a);

// src/algorithm/algorithm_utils.c
int		is_sorted(t_stack *stack);
int		find_min_value(t_stack *stack);
int		find_node_position(t_stack *stack, int value);

// src/algorithm/radix_sort.c
void	radix_sort(t_stack **a, t_stack **b);

// src/algorithm/small_sort.c
void	sort_three(t_stack **a);
void	sort_five(t_stack **a, t_stack **b);

// src/main.c
//void	print_stack(t_stack *stack);
int		main(int argc, char **argv);

// src/operations/push.c
void	pa(t_stack **stack_a, t_stack **stack_b, int print);
void	pb(t_stack **stack_a, t_stack **stack_b, int print);

// src/operations/swap.c
void	sa(t_stack **stack_a, int print);
void	sb(t_stack **stack_b, int print);
void	ss(t_stack **stack_a, t_stack **stack_b, int print);

// src/operations/reverse_rotate.c
void	rra(t_stack **stack_a, int print);
void	rrb(t_stack **stack_b, int print);
void	rrr(t_stack **stack_a, t_stack **stack_b, int print);

// src/operations/rotate.c
void	ra(t_stack **stack_a, int print);
void	rb(t_stack **stack_b, int print);
void	rr(t_stack **stack_a, t_stack **stack_b, int print);

// src/parsing/parsing_utils.c
long	ft_atol(const char *str);
void	free_stack_and_error(t_stack **stack);
void	free_split_local(char **arr);

// src/parsing/validation.c
int		is_valid_integer(const char *str);
int		has_duplicates(t_stack *stack);

// src/parsing/parsing.c
void	process_split_args(char **args, t_stack **stack_a);
void	parse_arguments(int argc, char **argv, t_stack **stack_a);

// src/utils/free_stack.c
void	free_stack(t_stack **stack);

// src/utils/stack_utils.c
void	ft_stack_add_back(t_stack **stack, t_stack *new_node);
int		ft_stack_size(t_stack *stack);
t_stack	*ft_stack_new(int value);
t_stack	*ft_stack_last(t_stack *stack);

#endif