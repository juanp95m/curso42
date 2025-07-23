#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char    *ft_strdup(char *src)
{
    int i;
    int len;
    char *duplicate;

    len = 0;
    i = 0;
    while (src[len])
        len++;
    duplicate = (char *)malloc (sizeof(char) * (len + 1));
    if (!duplicate)
        return (NULL);
    while (src[i])
    {
        duplicate[i] = src[i];
        i++;
    }
    duplicate[i] = '\0';
    return (duplicate);
}