#ifndef STL_file_process_
#define STL_file_process_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "../HashTable/config.h"
#include "../HashTable/realize.h"

struct File
{
    const char* name;
    Data_t*     buffer;
    size_t      size;
    size_t      nStrings;
};

File*
STL_Fread (const char* nameFile);

File* 
FileProcess (const char* nameFile);

void 
STL_Fprint (const char* nameFile, struct File* file);

File*
STL_Fclose (struct File* file);

#endif /* STL_file_process_ */
