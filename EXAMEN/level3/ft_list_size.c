#include <stdio.h>
#include "ft_list.h"

int	ft_list_size(t_list *begin_list)
{
    int i = 0;
    while (begin_list)
    {
        i++;
        begin_list = begin_list->next;
    }
    return (i);
}

int main()
{
    t_list node3 = {NULL, NULL}; // Último nodo, apunta a NULL
    t_list node2 = {&node3, NULL}; // Nodo intermedio, apunta al siguiente
    t_list node1 = {&node2, NULL}; // Primer nodo, apunta al siguiente

    printf("List size: %d\n", ft_list_size(&node1));
    return 0;
}