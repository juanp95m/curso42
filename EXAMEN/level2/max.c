#include <stdio.h>

int		max(int* tab, unsigned int len)
{
    unsigned int i;
    int result;

    if (len == 0)
        return (0);

    result = tab[0];
    i = 1;

    while (i < len)
    {
        if (tab[i] > result)
            result = tab[i];
        i++;
    }
    return (result);
}

int  main()
{
    int maximo;
    int numeros[] = {1,2,3,5,9,2};
    maximo = max(numeros, 6);
    printf("%d", maximo);
    return(0);
}