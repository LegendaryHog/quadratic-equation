#include <stdio.h>

char* my_strcat (char* str1, char* str2);

int main (void)
{
    char str1[] = "Poltor\0\0\0\0\0\0";
    char str2[] = "ashka";
    char* ptr;

    ptr = my_strcat (str1, str2);

    printf ("%s\n", ptr);

    for (int i = 0; i < 15; i++)
    {
        printf ("%c", *(ptr + i));
    }

    for (int i = 0; i < 13; i++)
    {
        printf ("\n%d", *(ptr + i));
    }

    return 0;
}

char* my_strcat (char* str1, char* str2)
{
    char* ptr = str1;

    while (*str1 != '\0')
    {
        str1++;
    }

    while (*str2 != '\0')
    {
        *str1++ = *str2++;
    }
    *str1 = '\0';

    return ptr;
}
