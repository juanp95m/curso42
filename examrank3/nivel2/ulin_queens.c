#include <stdio.h> // fprintf
#include <stdlib.h> // atoi
int     validation(int *table, int val, int col) // Verifica si la posicion (val, col) es segura
{
        for (int i = 0; i < col; i++) // Itera sobre las columnas anteriores
        {
                if (val == table[i]) // Chequea si esta en la misma fila
                        return (0); // Conflicto detectado
                if ((val - col) == table[i] - i) // Chequea diagonal principal
                        return (0); // Conflicto detectado
                if ((val + col) == table[i] + i) // Chequea diagonal secundaria
                        return (0); // Conflicto detectado
        }
        return (1); // Posicion segura
}
void    n_queen(int val, int col, int size, int *table) // Funcion recursiva
{
        if (col == size) // Caso base: todas las columnas llenas
        {
                for (int i = 0; i < size; i++) // Imprime la solucion
                {
                        fprintf(stdout, "%d ", table[i]); // Imprime indice de fila
                        if (i == size - 1) // Si es el ultimo
                                fprintf(stdout, "\n"); // Salto de linea
                }
                return ; // Retorna para seguir buscando (o terminar rama)
        }
        while (val < size) // Prueba filas desde 'val' hasta 'size'
        {
                if (validation(table, val, col)) // Si es valido colocar reina aqui
                {
                        table[col] = val; // Coloca la reina
                        n_queen(0, col + 1, size, table); // Recurre a siguiente col, fila 0
                }
                val++; // Prueba siguiente fila en esta columna
        }
        return ;
}
int     main(int ac, char **av)
{
        if (ac != 2) // Validacion de argumentos
                return (1);
        int size = atoi(av[1]); // Convierte argumento a int
        int table[size]; // Array VLA para el tablero
        n_queen(0, 0, size, table); // Inicia algoritmo: fila 0, col 0
        return (0);
}