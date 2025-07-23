#include <stdio.h>

int ft_strlen(char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int main (void)
{
    char *str = "crotolamo";
   int result = ft_strlen(str);
    printf("la palabra crotolamo mide: %d", result);
    return (0);
}