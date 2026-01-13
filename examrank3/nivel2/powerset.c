#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para malloc, free, atoi
#include <unistd.h>     // Para write

int	*nums;              // Array global con el conjunto de números del input
int	target;             // Suma objetivo que buscamos
int	actualbuff[100];    // Array que guarda el subconjunto actualbuff que estamos construyendo

void	powerset(int posnums, int size, int posact, int sum)  // posnums: posición en nums | size: tamaño de nums | posact: elementos en actualbuff | sum: suma acumulada
{
	if (sum == target)                      // Si la suma de los numeros que hay en actualbuff es igual al target
	{
		int	i = 0;                          // Inicializamos contador para imprimir
		while (i < posact)                  // Recorremos todos los elementos del subconjunto actualbuff
		{
			if (i > 0)                      // Si no es el primer elemento
				printf(" ");                // Imprimimos un espacio separador
			printf("%d", actualbuff[i++]);      // Imprimimos el elemento y avanzamos i
		}
		printf("\n");                       // Saltamos línea al terminar de imprimir el subconjunto
		return ;                            // Terminamos esta rama de recursión
	}
	if (posnums == size)                   // Si ya procesamos todos los elementos de nums
		return ;                            // Terminamos esta rama (caso base)
	powerset(posnums + 1, size, posact, sum);                        // Rama 1: NO incluimos nums[posnums] en el subconjunto
	actualbuff[posact] = nums[posnums];                                  // Guardamos el elemento actualbuff en el subconjunto
	powerset(posnums + 1, size, posact + 1, sum + nums[posnums]);    // Rama 2: SÍ incluimos nums[posnums] (aumentamos posact y sum)
}

int	main(int ac, char **av)
{
	int	i;
	
	i = -1;                                 // -1 para usar pre-incremento
	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2))))
		return (1);                         
	target = atoi(av[1]);                   // Convertimos el primer argumento a int (target)
	while (++i < ac - 2)                    // Recorremos los argumentos restantes
		nums[i] = atoi(av[i + 2]);          // Convertimos cada arg a int y lo guardamos en nums
	powerset(0, ac - 2, 0, 0);              // Llamamos a powerset: inicio en pos 0, 0 elementos seleccionados, suma 0
	free(nums);                             // Liberamos la memoria del array nums
	return (0);                             // Retornamos éxito
}