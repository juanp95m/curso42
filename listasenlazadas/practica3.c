#include <stdio.h>
#include <stdlib.h>

/*
** --------------------------------------------------------------------------
** Nivel 2: Los Movimientos del Tren (Operaciones)
** --------------------------------------------------------------------------
**
** Teoría:
** ---------
** Con nuestra fábrica de trenes lista, ahora podemos coreografiar sus
** movimientos. Todas las operaciones se basan en redirigir los punteros
** 'next' de los nodos afectados. Dibuja en un papel lo que quieres conseguir
** antes de escribir código, ¡es la mejor técnica!
**
** 1. Swap (sa): Intercambiar los dos primeros vagones.
** - Antes: head -> A -> B -> C
** - Después: head -> B -> A -> C
** Necesitas punteros al primer y segundo nodo para poder reordenar sus
** enganches 'next' y finalmente, actualizar 'head' para que apunte al
** nuevo primer nodo (el antiguo segundo).
**
** 2. Rotate (ra): Mover el primer vagón al final.
** - Antes: head -> A -> B -> C -> NULL
** - Después: head -> B -> C -> A -> NULL
** Necesitas encontrar el último nodo (C), hacer que su 'next' apunte al
** primer nodo (A), actualizar 'head' para que apunte al segundo (B), y
** finalmente, poner el 'next' del nuevo último nodo (A) a NULL.
**
** 3. Push (pa): Mover el primer vagón de una lista a la otra.
** - Antes: head_a -> A... | head_b -> B...
** - Después: head_a -> B -> A... | head_b -> (lo que seguía a B)
** Esta es la más compleja. Debes tomar el primer nodo de la lista origen,
** hacer que la cabeza de origen apunte a su segundo nodo, y luego
** enlazar el nodo movido al principio de la lista destino, actualizando
** la cabeza de destino.
**
** Objetivo del Ejercicio:
** -------------------------
** Implementar las funciones genéricas `swap`, `rotate` y `push`. El `main`
** se encargará de llamarlas y mostrar el resultado de cada operación.
*/

// El plano de nuestro vagón (sin cambios)
typedef struct s_node
{
    int           value;
    struct s_node *next;
} t_node;

// --- Prototipos de Utilidades (Nivel 1) ---
t_node *create_node(int value);
void   add_node_to_end(t_node **head, t_node *new_node);
t_node *find_last_node(t_node *head);
void   print_list(t_node *head);
void   free_list(t_node **head);

// --- Prototipos de Operaciones (Nivel 2) ---
void swap(t_node **head);
void rotate(t_node **head);
void push(t_node **dest, t_node **src);

// --- Funciones "envoltorio" para simular push_swap ---
void sa(t_node **head_a) { printf("Ejecutando sa:\n"); swap(head_a); }
void ra(t_node **head_a) { printf("Ejecutando ra:\n"); rotate(head_a); }
void pa(t_node **head_a, t_node **head_b) { printf("Ejecutando pa:\n"); push(head_a, head_b); }


int main(void)
{
    t_node *head_a = NULL;
    t_node *head_b = NULL;

    // Llenamos la lista 'a' con 10, 20, 30, 40
    for (int i = 1; i <= 4; i++)
        add_node_to_end(&head_a, create_node(i * 10));
    // Llenamos la lista 'b' con 99, 88
    add_node_to_end(&head_b, create_node(99));
    add_node_to_end(&head_b, create_node(88));

    printf("--- Estado Inicial ---\n");
    printf("Lista A: "); print_list(head_a);
    printf("Lista B: "); print_list(head_b);
    printf("----------------------\n\n");

    sa(&head_a);
    printf("Lista A: "); print_list(head_a);
    printf("----------------------\n\n");

    ra(&head_a);
    printf("Lista A: "); print_list(head_a);
    printf("----------------------\n\n");

    pa(&head_a, &head_b);
    printf("Lista A: "); print_list(head_a);
    printf("Lista B: "); print_list(head_b);
    printf("----------------------\n\n");

    pa(&head_a, &head_b);
    printf("Lista A: "); print_list(head_a);
    printf("Lista B: "); print_list(head_b);
    printf("----------------------\n\n");

    free_list(&head_a);
    free_list(&head_b);
    return (0);
}


// --- Implementación de Operaciones (Nivel 2) ---

// TODO: Rellena esta función
// Debe intercambiar los dos primeros nodos de la lista.
// No hace nada si la lista tiene 0 o 1 nodos.
void swap(t_node **head)
{
    t_node  *first;
    t_node  *second;
    t_node  *temp;
    if (!*head || !head || !(*head)->next)
        return;

    first = *head;
    second = first->next;
    temp = second->next;

    second->next = first;
    first->next = temp;
    *head = second;
}

// TODO: Rellena esta función
// Debe mover el primer nodo al final de la lista.
// No hace nada si la lista tiene 0 o 1 nodos.
void rotate(t_node **head)
{
    t_node  *first;
    t_node  *last;
    if (!*head || !head || !(*head)->next)
        return;
    first = *head;
    last = ft_find_last_node(*head);
    *head = first->next;
    last->next = first;
    first->next = NULL;
}

// TODO: Rellena esta función
// Debe tomar el primer nodo de la lista 'src' y ponerlo
// al principio de la lista 'dest'.
// No hace nada si la lista 'src' está vacía.
//Esta es la más compleja. Debes tomar el primer nodo de la lista origen,
//hacer que la cabeza de origen apunte a su segundo nodo, y luego
//enlazar el nodo movido al principio de la lista destino, actualizando
//la cabeza de destino.
void push(t_node **dest, t_node **src)
{
    t_node  *node_to_push;
    if (!*src || !src)
        return;
    node_to_push = *src;
    *src = node_to_push->next;
    node_to_push->next = *dest;
    *dest = node_to_push;
}


// --- Implementación de Utilidades (Nivel 1, ya hechas) ---
t_node *create_node(int value)
{
    t_node  *new_node;
    new_node = malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->value = value;
    new_node->next = NULL;
    return (new_node);
}

void add_node_to_end(t_node **head, t_node *new_node)
{
    t_node  *last;
    if (!*head || !head || !(*head)->next)
        return;
    new_node = *head;
    last = ft_find_last_node(*head);
    *head = new_node->next;
    last->next = new_node;
    new_node->next = NULL;

}

t_node *find_last_node(t_node *head)


void print_list(t_node *head)


void free_list(t_node **head)
