#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int ascending(int a, int b) { return (a <= b); }

static t_list *new_node(int data) {
    t_list *n = (t_list *)malloc(sizeof(t_list));
    if (!n) return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

static void print_list(t_list *lst) {
    while (lst) {
        printf("%d", lst->data);
        if (lst->next) printf(" -> ");
        lst = lst->next;
    }
    printf("\n");
}

int main(void) {
    // Lista: 4 -> 2 -> 5 -> 1
    t_list *a = new_node(4);
    t_list *b = new_node(2);
    t_list *c = new_node(5);
    t_list *d = new_node(1);
    a->next = b; b->next = c; c->next = d;

    printf("Original: ");
    print_list(a);

    t_list *sorted = sort_list(a, ascending);

    printf("Ordenada: ");
    print_list(sorted);

    // liberar
    while (sorted) { t_list *tmp = sorted; sorted = sorted->next; free(tmp); }
    return 0;
}
// deleted as requested
