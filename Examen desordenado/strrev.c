#include <stdio.h>

char    *ft_strrev(char *str)
{
    int i;
    int len;
    char temp;
    len = 0;

    while (str[len])
        len++;
    
    i = 0;
    len--;
    while (i < len)
    {
        temp = str[i];
        str[i] = str[len];
        str[len] = temp;

        i++;
        len--;
    }
    return (str);
}

int main ()
{
    char cadena[] = "mamawebo";
    printf("%s\n", cadena);
    ft_strrev(cadena);
    printf("%s", cadena);
    return 0;
}