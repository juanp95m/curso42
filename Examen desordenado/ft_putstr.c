#include <unistd.h>

void ft_putstr(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        write (1, &str[i], 1);
        i++;
    }
}

int main ()
{
    char *cadena = "como estan los maquinas";
    ft_putstr(cadena);
    return (0);
}