#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

int StrOfCharCompare (const void* str1, const void* str2);
//void FileSort (const char** Index, size_t Index_size);
size_t StrNum (char* Text, size_t Text_size);
void FixText (char** Text, size_t Text_size);
void MakeIndex (const char*** Index, char* Text, size_t Text_size);
void FileConvert (const char* source_name, char** Text, size_t Text_size);
void MakeOutputFile (const char* file_name, const char** Index, size_t Index_size);
void Qsort (void* Index, size_t Index_size, size_t size, int (*comparator) (const void* , const void*));

#endif // FUNCTIONS_H_INCLUDED
