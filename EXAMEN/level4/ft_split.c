#include <stdlib.h>
#include <stdio.h>

char  **ft_split(char *str)
{
    char **split = malloc(sizeof(char *) * 1000); // Limitar el número de palabras a 1000
    int i = 0;

    if (!split)
        return (NULL);

    while (*str)
    {
        while (*str < 33 && *str != '\0')
            str++;
        if (*str == '\0')
            break;
        char *start = str;
        while (*str >= 33)
            str++;
        int len = str - start;
        split[i] = malloc(sizeof(char) * (len + 1));
        if (!split[i])
            return (NULL); // Manejo de error
        int j = 0;
        while (j < len)
        {
            split[i][j] = start[j];
            j++;
        }
        split[i][len] = '\0';
        i++;
    }
    split[i] = NULL;
    return (split);
}

int main(void)
{
    char str[] = "Hola mundo 42!";
    char **result = ft_split(str);

    int i = 0;
    while (result[i])
    {
        printf("%s\n", result[i]);
        i++;
    }

    return (0);
}