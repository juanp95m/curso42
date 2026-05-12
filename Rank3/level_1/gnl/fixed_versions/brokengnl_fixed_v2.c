
#ifndef BUFFER_SIZE // 
# define BUFFER_SIZE 10 // 
#endif //

// borrado de "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] && s[i] != c) i++; // incluir dentro del while && s[i] "exista"
	if (s[i] == c) return (s + i);
	else return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	while (n-- > 0) // cambiar el --n por n--
		((char *)dest)[n] = ((char *)src)[n]; // cambiarar los n -1 por solo n
	return (dest);
}

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s && s[i]) i++; // añadir dentro del while && s "exista"
	return (i);
}

int	str_append_mem(char **s1, char *s2, int size2)
{
	int	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp) return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, int n)
{
	((char *)dest)[n] = '\0'; 
	ft_memcpy(dest, src, n);
	return (dest);
}

char	*get_next_line(int fd)
{
	// 1. Buffer estático: Guarda lo que sobra de lecturas anteriores (ej. "Mundo" después de "Hola\n")
	static char	b[BUFFER_SIZE + 1] = "";
	
	// 2. Acumulador: Aquí iremos construyendo la línea final poco a poco.
	char		*ret = NULL;
	
	// 3. Buscar salto de línea: Miramos si ya tenemos un '\n' en lo que sobró la última vez.
	char		*tmp = ft_strchr(b, '\n');

	// 4. Bucle principal: Mientras NO encontremos un salto de línea...
	while (!tmp)
	{
		// 4a. Vaciar buffer: Copiamos todo lo que hay en 'b' a 'ret' porque sabemos que no tiene '\n'.
		if (!str_append_str(&ret, b)) return (NULL); // Error de malloc

		// 4b. Leer más: Leemos del archivo para rellenar el buffer 'b' de nuevo.
		int read_ret = read(fd, b, BUFFER_SIZE);
		
		// 4c. Errores de lectura
		if (read_ret == -1) return (NULL);
		
		// 4d. Asegurar nulo: Ponemos \0 al final de lo leído para tratarlo como string.
		b[read_ret] = 0;

		// 4e. Fin del archivo (EOF): Si read devuelve 0 y no hay nada más que leer...
		if (read_ret == 0)
		{
			// Si habíamos acumulado algo en 'ret', lo devolvemos (última línea sin \n).
			if (*ret) return (ret);
			// Si no había nada, liberamos y devolvemos NULL (fin total).
			free(ret);
			return (NULL);
		}

		// 4f. Buscar de nuevo: Miramos si en lo nuevo que hemos leído hay un '\n'.
		tmp = ft_strchr(b, '\n');
	}

	// 5. Encontrado el '\n'!
	// Copiamos desde el inicio de 'b' HASTA el salto de línea (incluido) a 'ret'.
	// La longitud se calcula restando punteros: (posición del \n) - (inicio b) + 1.
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return (NULL); // Error de malloc
	}

	// 6. Limpiar buffer: Movemos lo que sobró (después del \n) al principio de 'b'.
	// Así estará listo para la próxima vez que llamemos a get_next_line.
	// Usamos tu ft_memmove simplificado o el bucle memcpy.
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1));

	// 7. ¡Éxito! Devolvemos la línea completa.
	return (ret);
}
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char *line;
	int fd = open(argv[1], O_RDONLY);
	(void)argc;
	
	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
