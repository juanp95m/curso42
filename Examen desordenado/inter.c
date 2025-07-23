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
        while (argv[1][i])
        {
            if (is_the_first_ocurrence(argv[1], i) && ft_strchr(argv[2], argv[1][i]))
                write (1, &argv[1][i], 1);
            i++;
        }
    }
    write (1, "\n", 1);
}