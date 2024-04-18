#ifndef STL_file_process_
#define STL_file_process_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "../HashTable/config.h"

struct File
{
    const char* name;
    char*       buffer;

#ifdef AVX
    Data_t*     words;
#endif

    size_t      size;
    size_t      nStrings;
};

File*
STL_Fread (const char* nameFile);

File* 
FileProcess (const char* nameFile);

File*
STL_Fclose (struct File* file);

#endif /* STL_file_process_ */
