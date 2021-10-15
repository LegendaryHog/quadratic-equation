#include <stdio.h>

char* my_strncpy (char* strcp, const char* str, size_t num);

int main (void)
{
    char str[] = "Poltorashka\0";
    char strcp[12] = "";

    //printf ("%d\n", my_strncpy (strcp, str, 15) - strcp);

    for (int i = 0; i < 11; i++)
    {
        printf ("%c", *(my_strncpy (strcp, str, 11) + i));
    }

    printf ("\n");

    for (int i = 0; i < 6; i++)
    {
        printf ("%c", *(my_strncpy (strcp, str, 6) + i));
    }

    return 0;
}

char* my_strncpy (char* strcp, const char* str, size_t num)
{
    char* ptr = strcp;

    while ((strcp - ptr < num) && (*str != '\0'))
    {
        *strcp++ = *str++;
    }

    *strcp = '\0';

    return ptr;
}
