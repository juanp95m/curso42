#include <stdlib.h>
#include <unistd.h>

int is_valid_pos(int *table, int x, int y)
{
	int i = 0;
	while (i < y)
	{
		if ((x == table[i]) || (x - y) == (table[i] - i) || (x + y) == (table[i] + i))
			return (0);
		i++;
	}
	return (1);
}

void print_table(int *table, int size)
{
	int i = 0;
	while (i < size)
	{
		char c = table[i++] + '0';
		write(1, &c, 1);
		if (i < size)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void n_queen(int *table, int y, int size)
{
	int x = 0;
	if (y == size)
		return (print_table(table, size));
	while(x < size)
	{
		if (is_valid_pos(table, x, y))
		{
			table[y] = x;
			n_queen(table, y + 1, size);
		}
		x++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return(1);
	int size = atoi(av[1]);
	int table[size];
	n_queen(table, 0, size);
	return (0);
}

/*Assignement name : n_queens
Expected files : *.c *.h
Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr
-------------------------------------------------------------------------

Escribe un programa que imprima todas las soluciones al problema de las n reinas
para un n dado como argumento.
No probaremos con valores negativos.
El orden de las soluciones no es importante.

Mostrarás las soluciones en el siguiente formato:
<p1> <p2> <p3> ... \n
donde pn son los índices de línea de la reina en cada columna, empezando por 0.

Por ejemplo, esto debería funcionar:
$> ./n_queens 2 | cat -e

$> ./n_queens 4 | cat -e
1 3 0 2$
2 0 3 1$

$> ./n_queens 7 | cat -e
0 2 4 6 1 3 5$
0 3 6 2 5 1 4$
etc...*/
