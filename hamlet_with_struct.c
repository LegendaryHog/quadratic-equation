#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define $meow printf("Meow from %s(%d)%s", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#define PHYPM HUINYA

#define SYMBOL_IS_USELESS *str == 'S' || *str == 'c' || *str == 'e' || *str == 'n' || *str == 'M' || *str == 'V' || *str == 'L' || *str == 'X' || *str == 'I' || *str == ' ' || *str == 'A' || *str == 'C'

typedef struct {
    char* strStart;
    size_t strsize;
} string;



char* From_File_to_buffer (void);

string* Index_Make (char* ptrBuff, size_t* indexsize);

void Str_bubble_Sort (string Index[], size_t indexsize);

int Str_Compare (const char* str1, const char* str2);

void Output_to_File (string Index[], size_t indexsize);

size_t Find_indexsize_and_str_make (char* ptrBuff);

char* Str_platinum (const char* str);

char Small_equal_Big (char c);

int Is_malloc (const char* str);




int main (void)
{
    size_t indexsize = 0;
    char* ptrBuff = From_File_to_buffer ();
    assert (ptrBuff != NULL);

    string* Index = Index_Make (ptrBuff, &indexsize);
    assert (Index != NULL);

    Str_bubble_Sort (Index, indexsize);

    Output_to_File (Index, indexsize);

    free (ptrBuff);

    return 0;
}

char* From_File_to_buffer (void)
{
    FILE* buffer = fopen ("test_find_indexsize.txt", "r");
    assert (buffer != NULL);

    fseek(buffer, 0, SEEK_SET);
    long start_of_File = ftell (buffer);

    fseek(buffer, 0, SEEK_END);
    long end_of_File = ftell (buffer);

    fseek(buffer, 0, SEEK_SET);
    long size_File = end_of_File - start_of_File;

    char* ptrBuff = (char*) calloc (size_File + 1, sizeof (char));
    assert (ptrBuff != NULL);

    long real_size_File = fread (ptrBuff + 1, sizeof (char), size_File, buffer);

    fclose (buffer);

    *ptrBuff = '\n';
    *(ptrBuff + real_size_File) = '\0';

    ptrBuff = (char*) realloc (ptrBuff, real_size_File + 2);
    assert (ptrBuff != NULL);

    return (char*)ptrBuff;
}

string* Index_Make (char* ptrBuff, size_t* indexsize)
{
    size_t i = 0;
    size_t strsize = 0;
    *indexsize = Find_indexsize_and_str_make (ptrBuff);

    printf ("%zd", *indexsize);

    string* Index =  (string*) calloc (*indexsize, sizeof (char*) + sizeof (size_t));
    assert (Index != NULL);

    while (i < *indexsize)
    {
        if (*ptrBuff == '\0')
        {
            if (Is_malloc (ptrBuff + 1) == 0)
            {
                assert (ptrBuff != NULL);
                Index[i].strStart = ptrBuff + 1;
                Index[i].strsize = strsize - 1;
                i++;
            }
            strsize = 0;
        }
        ptrBuff++;
        strsize++;
    }

    return (string*) Index;
}

int Str_Compare (const char* str1, const char* str2)
{
    assert (str1 != NULL);
    assert (str2 != NULL);

    str1 = Str_platinum (str1);
    str2 = Str_platinum (str2);
    while (Small_equal_Big (*str1) == Small_equal_Big (*str2) && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
        str1 = Str_platinum (str1);
        str2 = Str_platinum (str2);
    }

    return Small_equal_Big (*str2) - Small_equal_Big (*str1);
}

char* Str_platinum (const char* str)
{
    while ((*str > '\0' && *str < 'A') || (*str > 'Z' && *str < 'a') || *str > 'z')
    {
        str++;
    }
    return (char*)str;
}

char Small_equal_Big (char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    else
    {
        return c;
    }
}


void Str_bubble_Sort (string Index[], size_t indexsize)
{
    for (size_t j = 1; j < indexsize; j++)
    {
        for (size_t i = 0; i < indexsize - j; i++)
        {
            assert ((char*)Index[i].strStart != NULL);
            assert ((char*)Index[i + 1].strStart != NULL);
            if(Str_Compare (Index[i].strStart, Index[i + 1].strStart) < 0)
            {
                char* temp = Index[i].strStart;
                Index[i].strStart = Index[i + 1].strStart;
                Index[i + 1].strStart = temp;
            }
        }
    }
}

void Output_to_File (string Index[], size_t indexsize)
{
    FILE* sort_buffer = fopen ("sort_hamlet.txt", "w");

    for (size_t i = 0; i < indexsize; i++)
    {
        fputs (Index[i].strStart, sort_buffer);
        fputc ('\n', sort_buffer);
    }
    fclose (sort_buffer);
    free (Index);
}



size_t Find_indexsize_and_str_make (char* ptrBuff)
{
    size_t indexsize = 0;
    size_t strsize = 0;

    while (*ptrBuff != '\0')
    {
        if (*ptrBuff == '\n')
        {
            *ptrBuff = '\0';
            if (Is_malloc ((char*)(ptrBuff - strsize + 1)) == 0)
            {
                indexsize++;
            }
            strsize = 0;
        }
        ptrBuff++;
        strsize++;
    }

    return indexsize - 1;
}

int Is_malloc (const char* str)
{
    char* ptr = (char*)str;
    size_t counter_of_bad = 0;

    while (*str != '\0')
    {
        if (SYMBOL_IS_USELESS)
        {
            counter_of_bad++;
        }
        str++;
    }

    if (counter_of_bad > 0.75*(str - ptr - 1) || (str - ptr) < 7)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}




