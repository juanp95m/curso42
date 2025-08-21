#include <stdlib.h>

char    *ft_itoa(int nbr)
{
    int len = (nbr <= 0); // Contar espacio para signo o 0
    int temp = nbr;
    char *result;

    while (temp && ++len)
        temp /= 10;

    result = malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);

    result[len] = '\0';
    if (nbr < 0)
    {
        result[0] = '-';
        nbr = -nbr;
    }
    else if (nbr == 0)
        result[0] = '0';

    while (nbr)
    {
        result[--len] = (nbr % 10) + '0';
        nbr /= 10;
    }

    return (result);
}

#include <stdio.h>
#include <limits.h>

int main (void)
{
    printf("%s\n", ft_itoa(INT_MAX));
}
