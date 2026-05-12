#include <stdio.h> // fprintf
#include <stdlib.h> // atoi

int validation(int *table, int current, int col)
{
	for (int i = 0; i < col; i++) 
	{
		if (current == table[i])
				return (0); 
		if ((current - col) == table[i] - i) 
				return (0); 
		if ((current + col) == table[i] + i) 
				return (0); 
	}
	return (1); 
}
void	n_queen(int current, int col, int size, int *table) 
{
	if (col == size) 
	{
			for (int i = 0; i < size; i++) 
			{
					fprintf(stdout, "%d", table[i]); 
					if (i == size - 1) 
						fprintf(stdout, "\n"); 
					else
						fprintf(stdout, " ");
			}
			return ; 
	}
	while (current < size) 
	{
			if (validation(table, current, col)) 
			{
					table[col] = current; 
					n_queen(0, col + 1, size, table); 
			}
			current++; 
	}
	return ;
}
int main(int ac, char **av)
{
	if (ac != 2) 
			return (1);
	int size = atoi(av[1]); 
	int table[size]; 
	n_queen(0, 0, size, table); 
	return (0);
}
