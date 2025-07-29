#include <string.h>
#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
    int i;
    
    while (*s1)
    {
        i = 0;
        while (s2[i])
        {
            if (*s1 == s2[i])
                return ((char *)s1);
            i++;
        }
        s1++;
    }
    return (NULL);
}

int main ()
{
    const char  *s = "hola mundo";
    const char  *a = "aeiou";
    char *result = ft_strpbrk(s, a);
    printf("%s\n", result);
    return (0);
}