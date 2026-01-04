// ANTES DE NADA DESDE VIM EN MODO ESCAPE HAY QUE AÑADIR ESTE COMANDO:
// :%s/size_t/int  con esto cambiamos todos los size_t por int

//#ifndef BUFFER_SIZE
//# define BUFFER_SIZE 10
//#endif

//#include "get_next_line.h" //borrar esta libreria en incluir las siguientes:
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] != c) // incluir dentro del while && s[i] "exista"
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0) // cambiar el --n por n--
		((char *)dest)[n - 1] = ((char *)src)[n - 1]; // cambiarar los n - 1 por solo n
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	res = 0;
	while (*s) // añadir dentro del while && s "exista"
	{
		s++;
		res++;
	}
	return (res);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return (ft_memmove(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1; // sustituir esta linea por int j = ft_strlen((char *)src);
    // aqui debemos declarar e inicializar la i, int i = 0; 
	while (i >= 0) //sustituir por while (i <= j)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--; // cambiar i-- por i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;
	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		b[read_ret] = 0;
        //if (read_ret == 0)
        //{
        //  if (*ret)
        //      return (ret);
        //  free(ret);
        //  return (NULL);
        //}
        //temp = ft_strchr(b, '\n');
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL);
	}
    //ft_memmove(b, temp + 1, ft_strlen(temp + 1));
	return (ret);
}