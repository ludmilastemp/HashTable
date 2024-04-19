#include "fileProcess.h"

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

#ifdef BufferAsUnion
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

#ifdef BufferAsUnion
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
#ifdef BufferAsUnion
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
#ifdef BufferAsUnion
            buffer[iBuf + len / 16].str[len % 16] = *ptr;
#else 
            buffer[iBuf + len] = *ptr;
#endif
            ptr++;
            len++;
        }

        /**
         * Addition of '\0'
         */
        if (len > sizeWord - 1)
        {   
#ifdef BufferAsUnion 
            iBuf++;
#else 
            iBuf += sizeWord;
#endif

            for (; len < sizeWord * 2; len++)
            {
#ifdef BufferAsUnion
                buffer[iBuf].str[len - sizeWord] = 0;
#else
                buffer[iBuf + len - sizeWord] = 0;
#endif
            }
        }

        for (; len < sizeWord; len++)
        {
#ifdef BufferAsUnion
            buffer[iBuf].str[len] = 0;
#else
            buffer[iBuf + len] = 0;
#endif
        }

#ifdef BufferAsUnion
        iBuf++;
#else
        iBuf += sizeWord;
#endif
    }

#ifdef BufferAsUnion
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

#ifdef BufferAsUnion
    free (file->words);
    file->words    = nullptr;
#endif

    file->name     = nullptr;
    file->size     = 0;
    file->nStrings = 0;

    free (file);

    return nullptr;
}
