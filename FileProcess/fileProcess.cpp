#include "fileProcess.h"

void
Fread (File* file)
{
    assert (file);

    FILE* fp = fopen (file->name, "rb");
    if (fp == nullptr) return;

    struct stat buff = { 0 };

    fstat (fileno (fp), &buff); // error

    file->size = (size_t)buff.st_size;

    file->buffer = (Data_t*) aligned_alloc (sizeWord, (file->size + 1) * sizeof (char));
    if (file->buffer == nullptr) 
    {
        free (file);
        return;
    }

    file->size = fread ((char*)file->buffer, sizeof (char), file->size, fp);
    ((char*)file->buffer)[file->size] = 0; 
    file->nStrings = file->size / sizeWord;

    fclose (fp);
}

void
FileProcess (File* file)
{
    assert (file);

    Fread (file);
    if (file->buffer == nullptr) return;

    file->nStrings = 0;
    
    size_t sizeBuffer = file->size / sizeWord + 1;
    char* ptr = (char*)file->buffer;

    Data_t* buffer = (Data_t*) calloc (sizeBuffer, sizeof (Data_t));
    if (buffer == nullptr) return;
    
    for (int iBuf = 0; ptr != (char*)file->buffer + file->size - 1; 
         file->nStrings++)
    {
        /**
         * Check realloc
         */
        if (iBuf * sizeWord >= (int)sizeBuffer - sizeWord * 3)
        {
            sizeBuffer *= 2;
            
            Data_t* tmp = (Data_t*) realloc (buffer, sizeBuffer * sizeof (Data_t)); 
            if (tmp == nullptr) 
            {
                free (buffer);
                return;
            }
            buffer = tmp;
        }

        /**
         * Skip no alpha
         */
        while (ptr != (char*)file->buffer + file->size - 1
               && !isalpha (*ptr)) 
            ptr++; 

        /**
         * Copy word
         */
        int len = 0;
        while (ptr != (char*)file->buffer + file->size - 1 
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

    free (file->buffer);
    file->buffer = buffer;
    file->nStrings--;
}

void 
Fprint (const char* nameFile, 
        struct File* file)
{
    assert (nameFile);
    assert (file);

    FILE* fp = fopen (nameFile, "wb");
    if (fp == nullptr) return;

    for (size_t i = 0; i < file->nStrings; i++)
    {
        char* str = GetElemCharPtr (&file->buffer[i]);

        for (size_t j = 0; j < sizeWord; j++)
        {
            fprintf (fp, "%c", str[j]); 
        }
    }

    fclose (fp);
}

void 
Fclose (struct File* file)
{
    if (file == nullptr) return;
    
    if (file->buffer) free (file->buffer);
    file->buffer   = nullptr;
    file->name     = nullptr;
    file->size     = 0;
    file->nStrings = 0;
}
