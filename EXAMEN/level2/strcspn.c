#include <string.h>
#include <stddef.h>

char ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return (1);
        s++;
    }
    return (0);
}

size_t  ft_strcspn(const char *s, const char *reject)
{
    size_t i = 0;
    while (s[i] && !ft_strchr(reject, s[i]))
        i++;
    return (i);
}

#include <stdio.h>

int main (void)
{
    const char *s1 = "abcdef";
    const char *reject = "cd";
    size_t result = ft_strcspn(s1, reject);
    printf("%lu", (unsigned long)result);
}