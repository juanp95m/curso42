#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int *nums;
int target;
int buffer[100];

void	powerset(int ixn, int ixc, int sum, int size)
{
	if (ixn == size)
	{
		if (sum == target)
		{
			int i = 0;
			while (i < ixc)
			{
				if (i > 0)
					printf(" ");
				printf("%d", buffer[i++]);
			}
			printf("\n");
			return ;
		}
		return ;
	}
	powerset(ixn + 1, ixc, sum, size);
	buffer[ixc] = nums[ixn];
	powerset(ixn + 1, ixc + 1, sum + nums[ixn], size);
}

int main(int argc, char **argv)
{
	int i = -1;
	int ma = argc - 2;
	if (argc < 3 || !(nums = malloc(sizeof(int) * ma)))
		return (1);
	target = atoi(argv[1]);
	while (++i < ma)
		nums[i] = atoi(argv[i + 2]);
	powerset(0, 0, 0, ma);
	free(nums);
	return (0);
}
