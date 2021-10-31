#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "functions.h"

int StrOfCharCompare (const void* str1, const void* str2)
{
    assert(str1 != NULL && str2 != NULL);

    int i = 0;
    while (1)
    {
        if (((char*)str1)[i] != ((char*)str2)[i])
            break;
        if (((char*)str1)[i] == '\0')
            break;
        i++;
    }

    return (((char*)str1)[i] - ((char*)str2)[i]);
}

/*void FileSort (const char** Index, size_t Index_size)
{
    assert(Index != NULL);

    for (int nPass = 0; nPass < Index_size - 1; nPass++)
    {
        for (int i = 0; i < Index_size - 1; i++)
        {
            if (StrCompare(Index[i], Index[i+1]) > 0)
            {
                const char* temp = Index[i];
                Index[i] = Index[i+1];
                Index[i+1] = temp;
            }
        }
    }
} */

size_t StrNum (char* Text, size_t Text_size)
{
    assert(Text != NULL);

    size_t nStr = 0;
    for (int i = 0; i< Text_size; i++)
    {
        if (Text[i] == '\n')
            nStr++;
    }

    return nStr;
}

void FileConvert (const char* source_name, char** Text, size_t Text_size)
{
    assert(Text != NULL);

    FILE* source_file;
    source_file = fopen(source_name, "r") ;
    assert(source_file != NULL);

    char* temp_Text = *Text;
    for (int i = 0; i < Text_size; i++)
    {
        temp_Text[i] = fgetc(source_file);
    }
    temp_Text[Text_size - 1] = '\0';

    fclose(source_file);

    char* new_temp_Text = (char*) calloc(Text_size, sizeof(char));
    assert(new_temp_Text != NULL);

    for (int i = 0, j = 0; i < Text_size - 1; i++)
    {
        if (!(temp_Text[i] == '\n' && temp_Text[i + 1] == '\n'))
        {
            new_temp_Text[j] = temp_Text[i];
            j++;
        }
    }

    free(temp_Text);

    *Text = new_temp_Text;
}

void FixText (char** Text, size_t Text_size)
{
    assert(Text != NULL);

    char* temp_Text = *Text;
    for (int i = 0; i < Text_size; i++)
    {
        if (temp_Text[i] == '\n')
        {
            temp_Text[i] = '\0';
        }
    }

    *Text = temp_Text;
}

void MakeIndex (const char*** Index, char* Text, size_t Text_size)
{
    assert(Index != NULL && Text != NULL);

    const char** temp_Index = *Index;
    temp_Index[0] = &Text[0];
    for (size_t i = 1, j = 1; i < Text_size - 1; i++)
    {
        if (Text[i] == '\n' && Text[i + 1] != '\0')
        {
            temp_Index[j] = &Text[i + 1];
            j++;
        }
    }

    *Index = temp_Index;
}

void MakeOutputFile (const char* file_name, const char** Index, size_t Index_size)
{
    assert(Index != NULL);

    FILE* result_file;
    result_file = fopen(file_name, "w");
    assert(result_file != NULL);

    for (int i = 0; i < Index_size; i++)
    {
        for (int j = 0; ; j++)
        {
            fputc(Index[i][j], result_file);
            if (Index[i][j] == '\0')
                break;
        }
        fputc('\n', result_file);
    }

    fclose(result_file);
}

void Qsort (void* Index, size_t Index_size, size_t size, int (*comparator) (const void* , const void*))
{
    assert(Index != NULL);

    switch (size)
    {
        case sizeof(char):
            for (int nPass = 0; nPass < Index_size - 1; nPass++)
            {
                for (int i = 0; i < Index_size - 1; i++)
                {
                    if (comparator(((char**)Index)[i], ((char**)Index)[i+1]) > 0)
                    {
                        char* temp = ((char**)Index)[i];
                        ((char**)Index)[i] = ((char**)Index)[i+1];
                        ((char**)Index)[i+1] = temp;
                    }
                }
            } break;
        case sizeof(int):
            for (int nPass = 0; nPass < Index_size - 1; nPass++)
            {
                for (int i = 0; i < Index_size - 1; i++)
                {
                    if (comparator(((int**)Index)[i], ((int**)Index)[i+1]) > 0)
                    {
                        int* temp = ((int**)Index)[i];
                        ((int**)Index)[i] = ((int**)Index)[i+1];
                        ((int**)Index)[i+1] = temp;
                    }
                }
            } break;
        case sizeof(long long):
            for (int nPass = 0; nPass < Index_size - 1; nPass++)
            {
                for (int i = 0; i < Index_size - 1; i++)
                {
                    if (comparator(((long long**)Index)[i], ((long long**)Index)[i+1]) > 0)
                    {
                        long long* temp = ((long long**)Index)[i];
                        ((long long**)Index)[i] = ((long long**)Index)[i+1];
                        ((long long**)Index)[i+1] = temp;
                    }
                }
            } break;
        default:
            printf("Unknown type of data!");
            exit(-1);
    }
}
