#include <unistd.h>
#include <string.h>
#include <stdio.h>

int ft_strncmp(char *s1, char *s2, int size)
{
    int i = 0;

    while (s1[i] && s2[i] && i < size)
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

int main(int ac, char **av)
{
    int i;
    char c;
    char buf[99999];
    int b_read;
    int size;

    i = 0;
    if (ac != 2 || av[1] == NULL)
         return (1);
    size = strlen(av[1]);
    while ((b_read = read(0, &c, 1)) > 0)
    {
        if (b_read < 0)
        {
            write (2, "Error\n", 6);
            return (1);
        }
        buf[i] = c;
        i++;
    }
    buf[i] = '\0';
    i = 0;
    while (buf[i])
    {
        if (!ft_strncmp(&buf[i], av[1], size))
        {
            write (1, &buf[i], 1);
            i++;
        }
        else
        {
            for(int j = 0; j < size; j++)
                write (1, "*", 1);
            i += size;
        }
    }
    return (0);
}