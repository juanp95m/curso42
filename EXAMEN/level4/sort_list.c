#include "list.h"

t_list *sort_list(t_list* lst, int (*cmp)(int, int))
{
    int overflow;
    t_list *temp;

    temp = lst;
    while (lst->next)
    {
        if (((*cmp)(lst->data, lst->next->data)) == 0)
        {
            overflow = lst->data;
            lst->data = lst->data;
            lst->next->data = overflow;
            lst = temp;
        }
        else
            lst = lst->next;
    }
    return (lst);
}