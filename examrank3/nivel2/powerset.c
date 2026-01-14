#include <stdio.h>      // Para printf
#include <stdlib.h>     // Para malloc, free, atoi
#include <unistd.h>     // Para write

int	*nums;              // Array global con el conjunto de números del input
int	target;             // Suma objetivo que buscamos
int	buff[100];    // Array que guarda el subconjunto actualbuff que estamos construyendo

void	powerset(int posnums, int size, int posact, int sum)  // posnums: posición en nums | size: tamaño de nums | posact: elementos en actualbuff | sum: suma acumulada
{
    if (posnums == size)
    {
        if (sum == target)
        {
            int i = 0;
            while (i < posact)
            {
                if (i > 0)
                    printf(" ");
                printf("%d", buff[i++]);
            }
            printf("\n");
        }
        return ;
    }
    powerset(posnums + 1, size, posact, sum);
    buff[posact] = nums[posnums];
    powerset(posnums + 1, size, posact + 1, sum + nums[posnums]);
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