#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

int	*nums;
int	target; 
int	buffer[100];

void	powerset(int ixn, int size, int ixc, int sum)
{
	if (ixn == size)
	{
		if (sum == target)
		{
			int	i = 0;
			while (i < ixc)
			{
				if (i > 0)
					printf(" ");
				printf("%d", buffer[i++]);
			}
			printf("\n"); 
			return ;
		}
		return;
	}
	powerset(ixn + 1, size, ixc, sum);
	buffer[ixc] = nums[ixn];
	powerset(ixn + 1, size, ixc + 1, sum + nums[ixn]);
}

int	main(int ac, char **av)
{
	int	i;
	
	i = -1; 
	if (ac < 3 || !(nums = malloc(sizeof(int) * (ac - 2))))
		return (1); 
	target = atoi(av[1]); 
	while (++i < ac - 2)
		nums[i] = atoi(av[i + 2]);
	powerset(0, ac - 2, 0, 0);
	free(nums); 
	return (0); 
}
