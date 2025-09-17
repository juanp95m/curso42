#include <stdio.h>
#include <stdlib.h>

/*
** --------------------------------------------------------------------------
** Nivel 1: La Fábrica de Trenes (Funciones)
** --------------------------------------------------------------------------
**
** Teoría:
** ---------
** En el nivel 0, montaste el tren a mano. Ahora vamos a construir las
** máquinas que lo hacen por nosotros.
**
** 1. Abstracción: No queremos pensar en 'malloc' o en bucles 'while' cada
** vez que añadimos un vagón. Creamos funciones como `create_node` o
** `add_node_to_end` para ocultar esa complejidad.
**
** 2. Reutilización: Una vez que tu función `create_node` funciona, puedes
** usarla 1000 veces sin reescribir el código.
**
** 3. Doble Puntero (`**`): Recuerda, lo usamos en funciones que necesitan
** MODIFICAR el puntero 'head' original. Si la lista está vacía (`head` es
** NULL) y añadimos un nodo, la función necesita poder cambiar 'head' para
** que apunte al nuevo nodo. `add_node_to_end` y `free_list` lo necesitan.
**
** Objetivo del Ejercicio:
** -------------------------
** Rellenar las funciones de utilidad para crear, añadir, imprimir y
** liberar una lista. El `main` ya está escrito para usar esas funciones y
** construir una lista de 5 nodos.
*/

// El plano de nuestro vagón (sin cambios)
typedef struct s_node
{
    int           value;
    struct s_node *next;
} t_node;

// --- Declaraciones de nuestras herramientas (prototipos) ---
t_node *create_node(int value);
void   add_node_to_end(t_node **head, t_node *new_node);
t_node *find_last_node(t_node *head);
void   print_list(t_node *head);
void   free_list(t_node **head);


int main(void)
{
    t_node *head = NULL; // Nuestro jefe de estaciónheadieza sin tren.
    int i;

    printf("Construyendo un tren con 5 vagones...\n");
    for (i = 1; i <= 5; i++)
    {
        // Creamos un nuevo vagón y lo añadimos al final de la lista.
        add_node_to_end(&head, create_node(i * 10));
    }

    printf("\n--- Contenido del Tren ---\n");
    print_list(head);
    printf("--------------------------\n");

    free_list(&head);

    return (0);
}

// --- Implementación de las herramientas ---

// TODO: Rellena esta función
// Debe: 1. Reservar memoria para un nuevo nodo (malloc).
//       2. Comprobar si malloc falló.
//       3. Asignar el 'value' que recibe como parámetro.
//       4. Poner su puntero 'next' a NULL.
//       5. Devolver el nuevo nodo.
t_node *create_node(int value)
{
    t_node  *new_node;
    new_node = malloc(sizeof(t_node));
    if (new_node == NULL)
        return (NULL);
    new_node->value = value;
    new_node->next = NULL;
    return (new_node);
}

// TODO: Rellena esta función
// Debe: 1. Si la lista está vacía (*head es NULL), el nuevo nodo se
//          convierte en la cabeza de la lista.
//       2. Si la lista NO está vacía, encontrar el último nodo y
//          enganchar el nuevo nodo a su 'next'.
void add_node_to_end(t_node **head, t_node *new_node)
{
    if (!new_node)
        return;
    if (!*head)
        *head = new_node;
    else
    {
        t_node  *last = ft_find_last_node(*head);
        last->next = new_node;
    }
}

// TODO: Rellena esta función
// Debe: 1. Recorrer la lista hasta que el 'next' del nodo actual sea NULL.
//       2. Devolver ese último nodo.
//       3. Si la lista está vacía, debe devolver NULL.
t_node *find_last_node(t_node *head)
{
    t_node  *temp = head;
    if (!temp)
        return (NULL);
    while (temp->next)
    {
        temp = temp->next;
    }
    return (temp);
}

// TODO: Rellena esta función
// Debe: 1. Recorrer la lista e imprimir el valor de cada nodo.
//       2. Es igual al bucle que ya hiciste en el Nivel 0.
void print_list(t_node *head)
{
    t_node  *temp = head;
    if (!temp)
        return;
    while (temp)
    {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

// TODO: Rellena esta función
// Debe: 1. Recorrer la lista y liberar cada nodo uno por uno.
//       2. Es igual al bucle de liberación que vimos en el Nivel 0.
//       3. Al final, poner *head a NULL.
void free_list(t_node **head)
{
    t_node  *temp = *head;
    while (temp)
    {
        t_node *temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    *head = NULL;
    printf("\n¡Tren desmantelado y memoria liberada!\n");
}