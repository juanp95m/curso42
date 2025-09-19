                                         
#include "push_swap.h"
 // incluir tu cabecera

 //Comprueba si una cadena es un número entero válido.
int is_valid_integer(const char *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return (0);

    if (str[0] == '+' || str[0] == '-')
    {
        i = 1;
        // Si solo hay un signo sin numeros no es válido.
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

// Convierte una cadena a un tipo 'long' para detectar desbordamientos de 'int'.
static long ft_atol(const char *str)
{
    long result;
    int sign;

    result = 0;
    sign = 1;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

// Comprueba si existen valores duplicados en el stack.
int has_duplicates(t_stack *stack)
{
    t_stack *current; // Puntero para el nodo exterior del bucle.
    t_stack *indexnode;  // Puntero para el nodo interior, que compara con el exterior.

    current = stack; // Inicia el puntero 'current' en la cabeza del stack.
    // Recorre el stack nodo por nodo con el puntero 'current'.
    while (current)
    {
        indexnode = current->next; // 'indexnode' empieza en el nodo siguiente a 'current'.
        // Recorre el resto del stack con el puntero 'indexnode'.
        while (indexnode)
        {
            // Si el valor de 'current' es igual al de 'indexnode', se encontró un duplicado.
            if (current->value == indexnode->value)
                return (1); // Devuelve 1 (verdadero) indicando que hay duplicados.
            // Avanza 'indexnode' al siguiente nodo.
            indexnode = indexnode->next;
        }
        // Avanza 'current' al siguiente nodo para la próxima iteración.
        current = current->next;
    }
    return (0); // Devuelve 0 (falso).
}

// Libera toda la memoria asignada al stack y muestra un mensaje de error.
void free_stack_and_error(t_stack **stack)
{
    t_stack *current; // Puntero al nodo actual que se va a liberar.
    t_stack *tmp;     // Puntero temporal para no perder la referencia al siguiente nodo.

    current = *stack; // Empieza desde la cabeza del stack.
    // Bucle que se ejecuta mientras queden nodos en el stack.
    while (current)
    {
        tmp = current->next; // Guarda el puntero al siguiente nodo.
        free(current);       // Libera la memoria del nodo actual.
        current = tmp;       // Avanza al siguiente nodo.
    }
    *stack = NULL; // Asegura que el puntero original apunte a NULL.
    // Escribe "Error\n" en la salida de error estándar (stderr).
    write(2, "Error\n", 6);
    // Termina el programa con un código de error.
    exit(1);
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
			free_stack_and_error(stack_a);
		nbr = ft_atol(args[i]);
		if (nbr < INT_MIN || nbr > INT_MAX)
			free_stack_and_error(stack_a);
		new = ft_stack_new((int)nbr);
		ft_stack_add_back(stack_a, new);
		i++;
	}
	if (has_duplicates(*stack_a))
		free_stack_and_error(stack_a);
}
//para una unica cadena
void	parse_arguments(int argc, char **argv, t_stack **stack_a)
{
	int		i;
	long	nbr;
	t_stack	*new;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_integer(argv[i]))
			free_stack_and_error(stack_a);
		nbr = ft_atol(argv[i]);
		if (nbr < INT_MIN || nbr > INT_MAX)
			free_stack_and_error(stack_a);
		new = ft_stack_new((int)nbr);
		ft_stack_add_back(stack_a, new);
		i++;
	}
	if (has_duplicates(*stack_a))
		free_stack_and_error(stack_a);
}
