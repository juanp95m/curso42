#include <unistd.h>

int ft_strchr(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

int is_the_first_ocurrence(char *str, int pos)
{
    int     i = 0;
    while (i < pos)
    {
        if (str[i] == str[pos])
            return (0);
        i++;
    }
    return (1);
}

int main(int    argc, char  **argv)
{
    if (argc == 3)
    {
        int i = 0;
        // Primero procesamos la primera cadena
        while (argv[1][i])
        {
            if (is_the_first_ocurrence(argv[1], i))
                write (1, &argv[1][i], 1);
            i++;
        }
        
        // Luego procesamos la segunda cadena, pero solo los caracteres que no están en la primera
        i = 0;
        while (argv[2][i])
        {
            if (is_the_first_ocurrence(argv[2], i) && !ft_strchr(argv[1], argv[2][i]))
                write (1, &argv[2][i], 1);
            i++;
        }
    }
    write (1, "\n", 1);
}
