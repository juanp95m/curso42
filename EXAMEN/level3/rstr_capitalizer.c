#include <unistd.h>

void  rstr_capitalizer(char *str)
{
    int i = 0;
    while (str[i])
    {
        // Poner en minúscula cualquier letra mayúscula
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        // Si es letra y el siguiente es separador (espacio, tab) o fin de cadena, capitalizar
        if ((str[i] >= 'a' && str[i] <= 'z') && (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'))
            str[i] -= 32;
        write(1, &str[i], 1);
        i++;
    }
}

int main(int argc, char **argv)
{
	int	i = 1;
	
	if (argc == 1)
		write(1, "\n", 1);
	while (argc > i)
	{
		rstr_capitalizer(argv[i]);
		write(1, "\n", 1);
		i++;
	}
}