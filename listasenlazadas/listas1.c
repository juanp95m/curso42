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
    t_node *vagon1;
    t_node *vagon2;
    t_node *vagon3;
    t_node *head;

    // --- 1. Fabricar los vagones ---
    // TODO: Usa malloc para reservar memoria para vagon1, vagon2 y vagon3.
    
    vagon1 = malloc(sizeof(t_node));
    vagon2 = malloc(sizeof(t_node));
    vagon3 = malloc(sizeof(t_node));
    if (vagon1 == NULL || vagon2 == NULL || vagon3 == NULL)
    {
        // Si malloc falla, liberamos lo que ya se haya asignado y salimos.
        free(vagon1);
        free(vagon2);
        free(vagon3);
        return (1); // Salida de error
    }
    // --- 2. Rellenar los vagones con mercancía ---
    vagon1->value = 10;
    vagon2->value = 20;
    vagon3->value = 30;
    
    // --- 3. Enganchar los vagones en orden ---
    vagon1->next = vagon2;
    vagon2->next = vagon3;
    vagon3->next = NULL;

    // --- 4. Poner al jefe de estación en su sitio ---
    // El jefe de estación (head) debe apuntar al primer vagón.
    // TODO: Haz que 'head' apunte a 'vagon1'.
    head = vagon1;


    // --- 5. Recorrer e imprimir el tren ---
    printf("Contenido de la lista:\n");
    t_node *actual = head; // Un puntero temporal para no mover al jefe de estación.
    while (actual != NULL)
    {
        printf("%d\n", actual->value);
        actual = actual->next;
        // TODO: Imprime el valor del vagón 'actual'.
    }

    actual = head; // Reiniciamos 'actual' para liberar desde el principio.
    while (actual != NULL)
    {
        t_node *siguiente = actual->next; // Guarda el siguiente antes de liberar
        free(actual);
        actual = siguiente;
    }
    head = NULL; // Opcional: Evitar puntero colgante
    printf("Memoria liberada, fin del programa.\n");
    return (0);
}