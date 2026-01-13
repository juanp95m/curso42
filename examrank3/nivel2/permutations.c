#include <stdio.h>
#include <stdlib.h>

void swap(char *s1, char *s2)  
{
	char tmp = *s1;
	*s1 = *s2;       
	*s2 = tmp;       
}

void sort(char *str)
{
	int i = 0;
	while (str[i])
	{
		int j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

void permu(char *str, char *result, int *used, int pos, int size)  // Genera permutaciones recursivamente
{
	int i = 0;  // Índice para recorrer los caracteres disponibles
	if (pos == size)  // CASO BASE: si llenamos todas las posiciones
	{
		result[size] = '\0';  // Terminamos el string
		puts(result);  // Imprimimos esta permutación completa
		return ;  // Volvemos para buscar más permutaciones
	}

	while (i < size)  // Probamos con cada carácter de str
	{
		if (!used[i])  // Si este carácter NO ha sido usado en esta permutación
		{
			used[i] = 1;  // 1. Marcamos como usado
			result[pos] = str[i];  // 2. Lo colocamos en la posición actual de result
			permu(str, result, used, pos + 1, size);  // 3. RECURSIÓN: llenamos la siguiente posición
			used[i] = 0;  // 4. BACKTRACKING: desmarcamos para probar otras combinaciones
		}
		i++;  // Probamos con el siguiente carácter
	}
}

int main(int ac, char **av)  
{
	if (ac != 2)  // Verificamos que haya exactamente 1 argumento (además del nombre del programa)
		return (1);

	int size = 0;  // Variable para almacenar la longitud de la cadena
	while (av[1][size])  // Recorremos la cadena hasta encontrar '\0'
		size++;  // Contamos cada carácter

	sort(av[1]);  // Ordenamos la cadena alfabéticamente (para que las permutaciones salgan en orden)

	char *result = calloc(size + 1,sizeof(char));  // Reservamos memoria para construir cada permutación (+1 para '\0')
	int *used = calloc(size, sizeof(int));  // Array para marcar qué caracteres ya usamos (inicializado a 0)

	permu(av[1], result, used, 0, size);  // Generamos e imprimimos todas las permutaciones
	
	free(result);  // Liberamos la memoria de result
	free(used);  // Liberamos la memoria de used
	return (0); 
}