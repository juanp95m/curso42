#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char    *ft_strdup(char *src)
{
    int i;
    int len = 0;
    char *duplicate;
    while (src[len])
        len++;
    i = 0;
    duplicate = (char *)malloc (sizeof(char) * (len + 1));
    if (!duplicate)
        return(NULL);
   
    while (src[i])
    {
        duplicate[i] = src[i];
        i++;
    }
    duplicate[i] = '\0';
    return (duplicate);
}