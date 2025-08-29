#include <string.h>

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

size_t	ft_strspn(const char *s, const char *accept)
{
    size_t i = 0;
    while (s[i] && ft_strchr(accept, s[i]))
        i++;
    return (i);
}
#include <stdio.h>

int main(void)
{
    const char *s = "abcde123";
    const char *accept = "abcde";
    size_t result = ft_strspn(s, accept);
    printf("Resultado: %zu\n", result); // Debería imprimir 5
    return 0;
}