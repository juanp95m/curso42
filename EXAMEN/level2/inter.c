#include <unistd.h>

void    ft_inter(char *s1, char *s2)
{
    int i = 0;
    int j;
    char    array[128] = {0};

    while (s1[i])
    {
        j = 0;
        while (s2[j])
        {
            if (s1[i] == s2[j])
            {
                if (!array[(int)s1[i]])
                {
                    write (1, &s1[i], 1);
                    array[(int)s1[i]] = 1;
                }
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        ft_inter(argv[1], argv[2]);
    }
    write (1, "\n", 1);
    return 0;
}