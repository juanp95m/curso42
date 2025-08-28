#include <stdio.h>

int	ft_isspace(char c)
{
	return (c == 32 || c == '\t');
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_atoi_base(char *str, int str_base)
{
	int	i = 0;
	int	sign = 1;
	int	num = 0;
	int	result = 0;

	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num = str[i] - '0';
		else if (ft_isalpha(str[i]))
			num = ft_tolower(str[i]) - 'a' + 10;
		else
			break ;
		if (num >= str_base)
			break ;
		result = result * str_base + num;
		i++;
	}
	return (result * sign);
}

#include <stdio.h>

int	main(void)
{
    printf("--- Pruebas para ft_atoi_base ---\n\n");

    // Prueba básica
    printf("Input: \"101\", Base: 2 -> Esperado: 5, Obtenido: %d\n", ft_atoi_base("101", 2));
    
    // Prueba con base 10 y signo negativo
    printf("Input: \"-42\", Base: 10 -> Esperado: -42, Obtenido: %d\n", ft_atoi_base("-42", 10));
    
    // Prueba con hexadecimal (letras minúsculas)
    printf("Input: \"ff\", Base: 16 -> Esperado: 255, Obtenido: %d\n", ft_atoi_base("ff", 16));

    // Prueba con hexadecimal (letras mayúsculas)
    printf("Input: \"FF\", Base: 16 -> Esperado: 255, Obtenido: %d\n", ft_atoi_base("FF", 16));

    // Prueba con espacios al inicio
    printf("Input: \"   1a\", Base: 16 -> Esperado: 26, Obtenido: %d\n", ft_atoi_base("   1a", 16));

    // Prueba con un carácter inválido en medio (debería parar de leer)
    printf("Input: \"12G45\", Base: 16 -> Esperado: 18, Obtenido: %d\n", ft_atoi_base("12G45", 16));

    // Prueba con string vacío
    printf("Input: \"\", Base: 16 -> Esperado: 0, Obtenido: %d\n", ft_atoi_base("", 16));

    // Prueba con un '0' para ver si lo procesa
    printf("Input: \"10\", Base: 10 -> Esperado: 10, Obtenido: %d\n", ft_atoi_base("10", 10));
    
    return (0);
}
