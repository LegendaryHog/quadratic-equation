#include <stdio.h>

char* strangecat (char * str1, char * str2, size_t num);

int main (void)
{
    char str1[] = "Poltor\0\0\0\0\0\0";
    char str2[] = "ashka";
    char* ptr;

    ptr = strangecat (str1, str2, 3);

    printf ("%s\n", ptr);

    for (int i = 0; i < 13; i++)
    {
        printf ("%d\n", *(ptr + i));
    }

    return 0;
}

char* strangecat (char * str1, char * str2, size_t num)
{
    char* ptr = str1;

    while (*str1 != '\0')
    {
        str1++;
    }

    for (unsigned long long int i = 0; *str2 != '\0' && i < num; i++)
    {
        *str1++ = *str2++;
    }
    *str2 = '\0';

    return ptr;
}
