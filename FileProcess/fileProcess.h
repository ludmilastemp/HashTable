#ifndef STL_file_process_
#define STL_file_process_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include "../HashTable/config.h"
#include "../HashTable/dataAccessors.h"

struct File
{
    const char* name;
    Data_t*     buffer;
    size_t      size;
    size_t      nStrings;
    int         error;

    static const int FILE_NOT_FOUND = -1;
};

void Fread (File* file);

void FileProcess (File* file);

void Fprint (const char* fileName, struct File* file);

void Fclose (struct File* file);

#endif /* STL_file_process_ */
