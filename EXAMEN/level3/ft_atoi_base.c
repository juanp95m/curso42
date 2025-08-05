#include <stdio.h>

int	ft_atoi_base(const char *str, int str_base)
{
    int neg = 1;
    int result;
    int digit;

    while (*str < 33)
        str++;
    
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            neg = -neg;
        str++;
    }

    while (*str)
    {
        if (*str >= 'A' && *str <= 'F')
            digit = *str - 'A' + 10;
        else if (*str >= 'a' && *str <= 'f')
            digit = *str - 'a' + 10;
        else if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else
            break;
        
        if (*str >= str_base)
            break;

        result = result * str_base + digit;
        str++;
    }
    return (result * neg);
}


int main(void)
{
    printf("%d", ft_atoi_base("42a", 16));
}