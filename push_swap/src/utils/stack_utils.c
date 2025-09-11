/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:51:28 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/11 12:29:15 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Crea un nuevo nodo para el stack
t_stack *ft_stack_new(int value)
{
    t_stack *new_node; // Declara un puntero para el nuevo nodo

    new_node = malloc(sizeof(t_stack)); // Reserva memoria para el nodo
    if (!new_node) // Si la reserva falla, retorna NULL
        return (NULL);
    new_node->value = value; // Asigna el valor recibido al campo 'value'
    new_node->next = NULL; // Inicializa el puntero 'next' a NULL (no hay siguiente nodo)
    return (new_node); // Devuelve el puntero al nuevo nodo creado
}

// Encuentra el último nodo del stack
t_stack *ft_stack_last(t_stack *stack)
{
    if (!stack) // Si la pila está vacía, retorna NULL
        return (NULL);
    while (stack->next) // Recorre la pila hasta encontrar el último nodo
        stack = stack->next;
    return (stack); // Devuelve el último nodo
}

// Añade un nodo al final del stack
void    ft_stack_add_back(t_stack **stack, t_stack *new_node)
{
    t_stack *last; // Declara un puntero para el último nodo

    if (!stack || !new_node) // Si el puntero a la pila o el nuevo nodo es NULL, no hace nada
        return;
    if (!*stack) // Si la pila está vacía
    {
        *stack = new_node; // El nuevo nodo se convierte en el primer elemento
        return;
    }
    last = ft_stack_last(*stack); // Busca el último nodo de la pila
    last->next = new_node; // Enlaza el nuevo nodo al final de la pila
}