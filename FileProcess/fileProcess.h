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

void Fread (File* file);

void FileProcess (File* file);

void Fprint (const char* nameFile, struct File* file);

void Fclose (struct File* file);

#endif /* STL_file_process_ */
