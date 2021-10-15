#include <stdio.h>

char* my_strchr (const char* str, int ch);

int main (void)
{
    char str[] ="Poltorashka";

    printf ("%c\n", *my_strchr (str, 'k'));
    printf ("%d\n", my_strchr (str, 'k') - str + 1);
    printf ("%d\n", my_strchr (str, 'q'));

    return 0;
}

char* my_strchr (const char* str, int ch)
{
    while (*str != '\0')
    {
        if (*str == ch)
        {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}
