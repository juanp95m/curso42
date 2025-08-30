#include <stdlib.h>
#include <stdio.h>

int	*ft_range(int start, int end)
{
	int	i = 0;
	int	*array;
	int	size;
	
	if (start <= end)
		size = end - start + 1;
	else 
		size = start - end + 1;

	array = malloc(size * sizeof(int));
	if (!array)
		return (NULL);
	
	if (start <= end)
	{
		while (start <= end)
		{
			array[i] = start;
			i++;
			start++;
		}
	}
	else 
	{
		while (start >= end)
		{
			array[i] = start;
			i++;
			start--;
		}
	}
	return (array);
}


int	main()
{
	int	*arr = ft_range(1, 5);
	int	i = 0;

	while (i < 5)
		printf("%d, ", arr[i++]);
	free(arr);
 	return(0);
}