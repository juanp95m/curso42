#include "push_swap.h"
 
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