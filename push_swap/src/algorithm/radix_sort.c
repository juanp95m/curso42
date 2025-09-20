
#include "push_swap.h"


// --- 3. ALGORITMO RADIX PARA CASOS GRANDES ---

// Asigna a cada nodo un "índice" o ranking según su valor.
// El número más pequeño tendrá índice 0, el siguiente 1, y así sucesivamente.
static void	assign_indexes(t_stack *stack)
{
	t_stack	*current;
	t_stack	*runner;
	int		index;

	current = stack;
	while (current)
	{
		index = 0;
		runner = stack;
		while (runner)
		{
			if (current->value > runner->value)
				index++;
			runner = runner->next;
		}
		current->index = index;
		current = current->next;
	}
}

// El algoritmo Radix Sort.
void	radix_sort(t_stack **a, t_stack **b)
{
	int	i;
	int	j;
	int	size;
	int	max_bits;
	
	assign_indexes(*a); // Primero, simplificamos los números a índices.
	size = ft_stack_size(*a);
	max_bits = 0;
	// Calculamos cuántos bits necesitamos para representar el número más grande (el tamaño de la pila - 1).
	while (((size - 1) >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits) // Bucle por cada bit
	{
		j = 0;
		while (j < size) // Bucle por cada número de la pila
		{
			// Si el bit 'i' del índice del número actual es 0, lo movemos a 'b'.
			if ((((*a)->index >> i) & 1) == 0)
				pb(a, b, 1);
			else // Si es 1, lo rotamos.
				ra(a, 1);
			j++;
		}
		while (*b) // Devolvemos todo de 'b' a 'a'.
			pa(a, b, 1);
		i++;
	}
}
