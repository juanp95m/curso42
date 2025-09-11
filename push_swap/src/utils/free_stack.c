#include "push_swap.h"

void free_stack(t_stack **stack)
{
    t_stack *current;
    t_stack *tmp;

    current = *stack;
    while (current)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
    *stack = NULL;
}
