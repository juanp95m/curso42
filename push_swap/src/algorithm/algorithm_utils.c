#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0); // No está ordenada
		stack = stack->next;
	}
	return (1); // Está ordenada
}

// Encuentra el valor mínimo en la pila.
int	find_min_value(t_stack *stack)
{
	int	min;

	min = stack->value;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

// Encuentra la posición (índice, empezando en 0) de un número en la pila.
int	find_node_position(t_stack *stack, int value)
{
	int	position;

	position = 0;
	while (stack)
	{
		if (stack->value == value)
			return (position);
		stack = stack->next;
		position++;
	}
	return (-1); // No debería ocurrir si el valor existe
}