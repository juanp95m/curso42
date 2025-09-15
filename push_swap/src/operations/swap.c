/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:54:28 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/11 17:46:33 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/operations/swap.c
#include "push_swap.h"

// Intercambia los dos primeros elementos del stack dado.
static void	swap(t_stack **stack)
{
	t_stack	*first; // Apuntador al primer elemento
	t_stack	*second; // Apuntador al segundo elemento

	if (!stack || !*stack || !(*stack)->next) 
		return; // Si el stack es nulo o tiene menos de dos elementos, no hace nada
	first = *stack; // Guarda el primer elemento del stack
	second = first->next; // Guarda el segundo elemento del stack
	first->next = second->next; // El enganche del primer nodo ahora apunta al tercero
	second->next = first; // El enganche del segundo nodo ahora apunta al primero
	*stack = second; // El stack ahora comienza en el segundo elemento
}

void	sa(t_stack **stack_a, int print)
{
	swap(stack_a); // Realiza el swap en stack_a
	if (print) write(1, "sa\n", 3); // Imprime "sa" si print es verdadero
}

void	sb(t_stack **stack_b, int print)
{
	swap(stack_b); // Realiza el swap en stack_b
	if (print) write(1, "sb\n", 3); // Imprime "sb" si print es verdadero
}

void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	swap(stack_a); // Realiza el swap en stack_a
	swap(stack_b); // Realiza el swap en stack_b
	if (print) write(1, "ss\n", 3); // Imprime "ss" si print es verdadero
}