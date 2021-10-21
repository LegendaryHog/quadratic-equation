#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

void From_File_to_str (char** ptr_ptrOneg);

unsigned Index_Make (char* ptrOneg, char*** ptrIndex);

void Str_Sort (char* Index[], unsigned indexsize);

int Str_Compare (char* str1, char* str2);

void Output_to_File (char* Index[], unsigned indexsize);

unsigned Find_indexsize (char* ptrOneg);


int main (void)
{
    unsigned indexsize = 0;
    char** Index = NULL;
    char* ptrOneg = NULL;

    From_File_to_str (&ptrOneg);
    assert (ptrOneg != NULL);

    indexsize = Index_Make (ptrOneg, &Index);
    assert (Index != NULL);

    Str_Sort (Index, indexsize);
    Output_to_File (Index, indexsize);

    free (ptrOneg);

    return 0;
}

void From_File_to_str (char** ptr_ptrOneg)
{
    FILE* onegin = fopen ("onegin.txt", "r");
    assert (onegin != NULL);

    long int start_of_File = ftell (onegin);
    fseek(onegin, start_of_File, SEEK_END);
    long int end_of_File = ftell (onegin);
    fseek(onegin, start_of_File, SEEK_SET);
    long int size_File = end_of_File - start_of_File;

    printf ("%ld\n", size_File);

    *ptr_ptrOneg = (char*) calloc (size_File, sizeof (char));
    assert (*ptr_ptrOneg != NULL);

    long int  real_size_File = fread (*ptr_ptrOneg, sizeof (char), size_File, onegin);

    fclose (onegin);
    printf ("%ld\n", real_size_File);

    *(*ptr_ptrOneg + real_size_File) = '\0';

    *ptr_ptrOneg = (char*) realloc ((void*)*ptr_ptrOneg, real_size_File + 1);
    assert (*ptr_ptrOneg != NULL);
}

unsigned Index_Make (char* ptrOneg, char*** ptrIndex)
{
    unsigned i = 1;

    unsigned indexsize = Find_indexsize (ptrOneg);

    printf ("%u", indexsize);

    *ptrIndex = (char**) calloc (indexsize, sizeof (char*));
    assert (*ptrIndex != NULL);

    *ptrIndex[0] = ptrOneg;

    while (i < indexsize)
    {
        if (*ptrOneg = '\0')
        {
            *ptrIndex[i] = ptrOneg;
            i++;
        }
        ptrOneg++;
    }

    return indexsize;
}

int Str_Compare (char* str1, char* str2)
{
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
    }

    return *str2 - *str1;
}

void Str_Sort (char* Index[], unsigned indexsize)
{
    for (int j = 1; j < indexsize; j++)
    {
        for (int i = 0; i < indexsize - j; i++)
        {
            assert ((char*)Index[i] != NULL);
            assert ((char*)Index[i + 1] != NULL);
            if(Str_Compare ((char*)Index[i], (char*)Index[i + 1]) > 0)
            {
                char* temp = (char*)Index [i];
                Index[i] = Index[i + 1];
                Index[i + 1] = temp;
            }
        }
    }
}

void Output_to_File (char* Index[], unsigned indexsize)
{
    FILE* sort_onegin = fopen ("sort_onegin.txt", "w");

    for (int i = 0; i < indexsize; i++)
    {
        fputs ((char*)Index[i], sort_onegin);
        fputc ('\n', sort_onegin);
    }
    fclose (sort_onegin);
    free (Index);
}

unsigned Find_indexsize (char* ptrOneg)
{
    unsigned indexsize = 0;

    while (*ptrOneg != '\0')
    {
        if (*ptrOneg == '\n')
        {
            *ptrOneg = '\0';
            indexsize++;
        }
        ptrOneg++;
    }

    return indexsize + 1;
}


