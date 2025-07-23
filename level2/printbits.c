#include <unistd.h>
void printbits(unsigned char octet)
{
    int i;
    i = 7;
    while (i >= 0)
    {
        if ((octet >> i) & 1)
            write (1,"1", 1);
        else
            write (1, "0", 1);
        i--;
    }
}

int main()
{
	unsigned char octet = 255;
	printbits(octet);
    return (0);
}