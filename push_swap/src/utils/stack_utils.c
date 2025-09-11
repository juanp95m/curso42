/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:51:28 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/10 18:56:27 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Crea un nuevo nodo para el stack
t_stack *ft_stack_new(int value)
{
    t_stack *new_node;

    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return (NULL);
    new_node->value = value;
    new_node->next = NULL;
    return (new_node);
}

// Encuentra el último nodo del stack
t_stack *ft_stack_last(t_stack *stack)
{
    if (!stack)
        return (NULL);
    while (stack->next)
        stack = stack->next;
    return (stack);
}

// Añade un nodo al final del stack
void    ft_stack_add_back(t_stack **stack, t_stack *new_node)
{
    t_stack *last;

    if (!stack || !new_node)
        return;
    if (!*stack)
    {
        *stack = new_node;
        return;
    }
    last = ft_stack_last(*stack);
    last->next = new_node;
}