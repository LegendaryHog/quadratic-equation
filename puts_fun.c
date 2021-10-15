#include <stdio.h>

int my_puts (const char* s);

int main (void)
{
    char s[] = "Poltorashka";
    char a[] = "";
    printf ("%d\n", my_puts (s));
    printf ("%d\n", my_puts (a));
    return 0;
}

int my_puts (const char* s)
{
    int test = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
       putchar (s[i]);
       test++;
    }

    putchar ('\n');

    if (test == 0)
    {
        return EOF;
    }
    return test;
}
