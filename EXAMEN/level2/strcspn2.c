#include <string.h>

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return (1);
        s++;
    }
    return (0);
}

size_t  *ft_strcspn(const char *s, const char *reject)
{
    size_t i = 0;
    while (s[i] && !ft_strchr(reject, s[i]))
        i++;
    return (i);
}