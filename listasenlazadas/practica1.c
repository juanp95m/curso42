#include <stdio.h>
#include <stdlib.h>
/* --------------------------------------------------------------------------
**
** Teoría:
** ---------
** 1. El 'struct': Es el plano para fabricar nuestros "vagones" (nodos).
** Cada vagón tendrá un 'valor' y un "enganche" ('next') para apuntar al
** siguiente.
**
** 2. malloc: Es nuestra fábrica de vagones. Le pedimos memoria al sistema
** para un nuevo vagón y nos devuelve la "dirección" de ese vagón recién
** creado. Si no hay memoria, devuelve NULL.
**
** 3. El operador '->': Es la forma de "entrar" en un vagón del que tenemos
** su dirección. Si tenemos `t_node *vagon;`, para ver su valor usamos
** `vagon->value` y para manipular su enganche usamos `vagon->next`.
**
** 4. El puntero 'head': Es nuestro "jefe de estación". Un simple puntero que
** siempre sabe dónde está el PRIMER vagón del tren. Si vale NULL, la vía
** está vacía.
**
** Objetivo del Ejercicio:
** -------------------------
** Crear una mini-lista de 3 nodos de forma manual, enlazarla, recorrerla
** para imprimir sus valores y, muy importante, liberar la memoria al final.
*/

// Este es el plano de nuestro vagón.
typedef struct s_node
{
    int           value;
    struct s_node *next;
}                 t_node;


int main(void)
{
    // Punteros para nuestros 3 futuros vagones y para el jefe de estación.

    // --- 1. Fabricar los vagones ---
    // TODO: Usa malloc para reservar memoria para vagon1, vagon2 y vagon3.
    t_node  *head;
    t_node  *nodo1;
    t_node  *nodo2;
    t_node  *nodo3;

    nodo1 = malloc(sizeof(t_node));
    nodo2 = malloc(sizeof(t_node));
    nodo3 = malloc(sizeof(t_node));

    if (!nodo1 || !nodo2 || !nodo3)
    {
        free(nodo1);
        free(nodo2);
        free(nodo3);
        return (1);
    }

        // Si malloc falla, liberamos lo que ya se haya asignado y salimos.

    // --- 2. Rellenar los vagones con mercancía ---
    nodo1->value = 10;
    nodo2->value = 20;
    nodo3->value = 30;
    
    // --- 3. Enganchar los vagones en orden ---
    nodo1->next = nodo2;
    nodo2->next = nodo3;
    nodo3->next = NULL;

    // --- 4. Poner al jefe de estación en su sitio ---
    // El jefe de estación (head) debe apuntar al primer vagón.
    // TODO: Haz que 'head' apunte a 'vagon1'.
    head = nodo1;

    // --- 5. Recorrer e imprimir el tren ---
    t_node  *temp = head;
    while (temp)
    {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
    temp = head;
    while (temp)
    {
        t_node  *temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    head = NULL;
    return (0);
}