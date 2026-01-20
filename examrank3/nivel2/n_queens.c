#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int validation(int *table, int val, int col)
{
	for(int i = 0; i < col; i++)
	{
		if (val == table[i])
			return (0);
		if ((val - col) == (table[i] - i))
			return (0);
		if ((val + col) == (table[i] + i))
			return (0); 
	}
	return (1);
}

void	n_queens(int *table, int val, int col, int size)
{
	if (col == size)
	{
		for (int i = 0; i < size; i++)
		{

			fprintf(stdout, "%d", table[i]);
			if (i == size - 1)
				fprintf(stdout, "\n");
			else if (i != size - 1)
				fprintf(stdout, " ");
		}
		return ;
	}
	while (val < size)
	{
		if (validation(table, val, col))
		{
			table[col] = val;
			n_queens(table, 0, col + 1, size);
		}
		val++;
	}
}

int main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int size = atoi(av[1]);
	int table[size];
	n_queens(table, 0, 0, size);
	return (0);
}
