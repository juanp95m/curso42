#include "push_swap.h"

// Convierte una cadena a un tipo 'long' para detectar desbordamientos de 'int'.
long ft_atol(const char *str)
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

// Libera toda la memoria asignada al stack y muestra un mensaje de error.
void free_stack_and_error(t_stack **stack)
{
    // Reutilizamos la función genérica de liberación
    free_stack(stack);
    // Escribe "Error\n" en la salida de error estándar (stderr).
    write(2, "Error\n", 6);
    // Termina el programa con un código de error.
    exit(1);
}
// Helper local para liberar el resultado de ft_split
void	free_split_local(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}