#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "functions.h"

int main()
{
    const char* source_name = "Onegin_text.txt";
    struct stat st;
    stat(source_name, &st);
    size_t Text_size = st.st_size + 1;

    char* Text = (char*) calloc(Text_size, sizeof(char));
    assert(Text != NULL);

    FileConvert(source_name, &Text, Text_size);
    assert(Text != NULL);

    size_t Index_size = StrNum(Text, Text_size);
    Text_size -= Index_size;

    Text = (char*) realloc(Text, Text_size);
    assert(Text != NULL);
    Text[Text_size - 1] = '\0';

    const char** Index = (const char**) calloc(Index_size, sizeof(char*));
    assert(Index != NULL);

    MakeIndex(&Index, Text, Text_size);
    assert(Index != NULL);

    FixText(&Text, Text_size);

    //FileSort(Index, Index_size);

    Qsort(Index, Index_size, sizeof(char), StrOfCharCompare);

    const char* result_name = "Result.txt";
    MakeOutputFile(result_name, Index, Index_size);

    printf("The answer is written in <%s>\n", result_name);

    free(Text);
    free(Index);

    return 0;
}


