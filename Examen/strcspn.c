#include <string.h>
#include <stddef.h>
#include <stdio.h>

static int ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return (1);
        s++;
    }
    return (0);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
    size_t i;
    i = 0;
    while (s[i] && !ft_strchr(reject, s[i]))
        i++;
    return (i);
}

int main ()
{
    const char *cadena1 = "abbbbbbbcccdijk";
    const char *rechazo = "cd";
    size_t result = ft_strcspn(cadena1, rechazo);
    printf ("%zu", result);
    return (0);
}