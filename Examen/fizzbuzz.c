#include <unistd.h>

void ft_putnbr(int n)
{
    char digit;
    if (n > 9)
        ft_putnbr( n / 10);
    digit = (n % 10) + 48;
    write(1, &digit, 1);
}

int main (void)
{
    int i;
    i = 0;
    while (i <= 100)
    {
        if (i % 15 == 0)
            write (1, "fizzbuzz", 8);
        else if (i % 5 == 0)
            write (1, "fizz", 4);
        else if (i % 3 == 0)
            write (1, "buzz", 4);
        else
            ft_putnbr(i);
        i++;
        write (1, "\n", 1);
    }
}