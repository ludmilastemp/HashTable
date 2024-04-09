#ifndef STL_file_process_
#define STL_file_process_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

struct String  /// word - ?
{
    const char* str;
    int         len;
}; 
// a  - 1
// strcmp ("a", "and") = 0 

struct File
{
    const char* name;
    char*       buffer;
    size_t      size;
    int         nStrings;
    String*     strings;
};

File*
STL_Fread (const char* nameFile);

File*
STL_SplitFileIntoLines (const char* nameFile);

int /// File* ... return nullptr;
STL_Fclose (struct File* file);

#endif /* STL_file_process_ */
