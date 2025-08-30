#include <stdio.h>

int	    is_power_of_2(unsigned int n)
{
    unsigned int test = 1;

    while (test <= n)
    {
        if (test == n)
            return (1);
        else
            test *= 2;
    }
    return (0);
}