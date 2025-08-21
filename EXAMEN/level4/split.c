#include <stdlib.h>

char    **ft_split(char *str)
{
    char **split = malloc(sizeof(char *) * 1000);
    int i = 0;

    if (!split)
        return(NULL);
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
        if (!split)
            return (NULL);
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