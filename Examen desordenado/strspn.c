#include <string.h>
#include <stdio.h> // Para poder usar printf
#include <stddef.h> // Para el tipo size_t

static int  ft_strchr(const char *s, int c)
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
    size_t  i = 0;
    
    while (s[i] && ft_strchr(accept, s[i]))
            i++;
    return (i);  
}

int main ()
{
    const char *cadena = "aabbcad";
    const char *aceptado = "ab";
    size_t resultado;
    resultado = ft_strspn(cadena, aceptado);
    printf("%zu", resultado);
    return 0;
}