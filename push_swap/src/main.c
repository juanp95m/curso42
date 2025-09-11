/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-m <jperez-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:21:15 by jperez-m          #+#    #+#             */
/*   Updated: 2025/09/10 18:39:55 by jperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// --- Función temporal para imprimir la pila ---
void    print_stack(t_stack *stack)
{
    printf("--- Contenido del Stack ---\n");
    if (!stack)
    {
        printf("(Vacío)\n");
        return;
    }
    while (stack)
    {
        printf("Valor: %d\n", stack->value);
        stack = stack->next;
    }
    printf("---------------------------\n");
}

int main(int argc, char **argv)
{
    t_stack *stack_a;

    stack_a = NULL;
    // Si no hay argumentos, no hacemos nada (como debe ser)
    if (argc < 2)
        return (0);
    
    // 1. Llamamos a tu función de parsing
    parse_arguments(argc, argv, &stack_a);

    // 2. Imprimimos el resultado para verificar
    printf("¡Parsing completado con éxito!\n");
    print_stack(stack_a);

    // 3. (Importante) Liberamos la memoria al final
    free_stack(&stack_a); // Liberar la memoria del stack
    
    return (0);
}