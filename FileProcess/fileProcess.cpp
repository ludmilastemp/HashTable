#include "fileProcess.h"

static char*
GetElemPtr (void* buffer, int nElem, int len);

static char*
GetElemPtr (void* buffer, int nElem, int len)
{
    #ifdef UNION
        return &((Data_t*)buffer)[nElem + len / 16].str[len % 16];
    #else 
        return &((char*)buffer)[nElem * 16 + len];
    #endif
}

File* 
STL_Fread (const char* nameFile)
{
    assert (nameFile);

    FILE* fp = fopen (nameFile, "rb");
    if (fp == nullptr) return nullptr;

    File* file = (File*) calloc (1, sizeof (File));
    if (file == nullptr) return nullptr;

    struct stat buff = { 0 };

    file->name = nameFile;
    fstat (fileno (fp), &buff); // error

    file->size = (size_t)buff.st_size;

    file->buffer = (char*) calloc (file->size, sizeof (char));
    if (file->buffer == nullptr) 
    {
        free (file);
        return nullptr;
    }

    file->size = fread (file->buffer, sizeof (char), file->size, fp);

#ifdef UNION
    file->words = nullptr;
#endif

    fclose (fp);

    return file;
}

File* 
FileProcess (const char* nameFile)
{
    assert (nameFile);

    File* file = STL_Fread (nameFile);
    if (file == nullptr) return nullptr;

    file->nStrings = 0;
    
    size_t sizeBuffer = file->size / 16;
    char* ptr = file->buffer;

#ifdef UNION
    Data_t* buffer = (Data_t*) calloc (sizeBuffer, sizeof (Data_t));
#else 
    char* buffer = (char*) calloc (sizeBuffer, sizeof (char));
#endif

    if (buffer == nullptr) return nullptr;
    
    for (int iBuf = 0; ptr != file->buffer + file->size - 1; 
         file->nStrings++)
    {
        /**
         * Check realloc
         */
        if ((size_t)iBuf * 16 >= sizeBuffer - sizeWord * 3)
        {
            sizeBuffer *= 2;
            
#ifdef UNION
            Data_t* tmp = (Data_t*) realloc (buffer, sizeBuffer * sizeof (Data_t));
#else 
            char* tmp = (char*) realloc (buffer, sizeBuffer * sizeof (char));
#endif           

            if (tmp == nullptr) 
            {
                STL_Fclose (file);
                return nullptr;
            }
            buffer = tmp;
        }

        /**
         * Skip no alpha
         */
        while (ptr != file->buffer + file->size - 1
               && !isalpha (*ptr)) 
            ptr++; 

        /**
         * Copy word
         */
        int len = 0;
        while (ptr != file->buffer + file->size - 1 
               && isalpha (*ptr))
        {
            *GetElemPtr (buffer, iBuf, len) = *ptr;
            ptr++;
            len++;
        }

        /**
         * Addition of '\0'
         */
        if (len > sizeWord - 1)
        {   
            for (; len < sizeWord * 2; len++)
            {
                *GetElemPtr (buffer, iBuf, len) = 0;
            }

            iBuf++;
        }

        for (; len < sizeWord; len++)
        {
            *GetElemPtr (buffer, iBuf, len) = 0;
        }

        iBuf++;
    }

#ifdef UNION
    file->words  = buffer;
#else
    free (file->buffer);
    file->buffer = buffer;
    file->size   = sizeBuffer;
#endif

    file->nStrings--;

    return file;
}

File* 
STL_Fclose (struct File* file)
{
    if (file == nullptr) return 0;
    
    free (file->buffer);
    file->buffer   = nullptr;

#ifdef UNION
    free (file->words);
    file->words    = nullptr;
#endif

    file->name     = nullptr;
    file->size     = 0;
    file->nStrings = 0;

    free (file);

    return nullptr;
}
