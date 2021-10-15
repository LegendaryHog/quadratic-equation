#include <stdio.h>

size_t my_strlen (const char* str);

int main (void)
{
    char str[] = "Poltorashka";
    printf ("%zd", my_strlen (str));
    return 0;
}

size_t my_strlen (const char* str)
{
    unsigned long long int len = 0;

    while (*str != '\0')
    {
        (char*)str++;
        len++;
    }
    return len;
}
