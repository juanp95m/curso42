#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 2)
    {   
        int i = 0;
        int j;
        while (argv[1][i])
        {
            if (argv[1][i] < 33 && argv[1][i + 1] >= 33 && argv[1][i + 1] <= 126)
                j = i + 1;
            i++;
        }
        while (argv[1][j] >= 33 && argv[1][j] <= 126)
        {
            write (1, &argv[1][j], 1);
            j++;
        }
    }
    write (1, "\n", 1);
    return (0);
}