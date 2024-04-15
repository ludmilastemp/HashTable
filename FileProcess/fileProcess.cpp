#include "fileProcess.h"

File* STL_Fread (const char* nameFile)
{
    assert (nameFile);

    File* file = (File*) calloc (1, sizeof (File));
    assert (file);

    struct stat buff = { 0 };

    FILE* fp = fopen (nameFile, "rb");
    assert (fp);

    file->name = nameFile;
    fstat (fileno (fp), &buff);

    file->size = (size_t)buff.st_size;

    file->buffer = (char*) calloc (file->size, sizeof (char));
    assert (file->buffer);

    file->size = fread (file->buffer, sizeof (char), file->size, fp);

    fclose (fp);

    return file;
}

File* FileProcess (const char* nameFile)
{
    assert (nameFile);

    File* file = STL_Fread (nameFile);
    assert (file);

    file->nStrings = 0;
    
    size_t sizeBuffer = file->size;
    char* ptr = file->buffer;

    char* buffer = (char*) calloc (sizeBuffer, sizeof (char));
    assert (buffer);
    
    for (int iBuf = 0; ptr != file->buffer + file->size - 1; 
         iBuf += sizeWord, file->nStrings++)
    {
        /**
         * Check realloc
         */
        if ((size_t)iBuf >= sizeBuffer - sizeWord * 3)
        {
            sizeBuffer *= 2;
            buffer = (char*) realloc (buffer, sizeBuffer * sizeof (char));
            assert (buffer);
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
            buffer[iBuf + len] = *ptr;
            ptr++;
            len++;
        }

        /**
         * Addition of '\0'
         */
        if (len > sizeWord - 1)
        {
            for (; len < sizeWord * 2; len++)
                buffer[iBuf + len] = 0;
            iBuf += sizeWord;
        }

        for (; len < sizeWord; len++)
            buffer[iBuf + len] = 0;
    }

    free (file->buffer);
    file->buffer = buffer;
    file->size   = sizeBuffer;
    file->nStrings--;

    return file;
}

File* STL_Fclose (struct File* file)
{
    if (file == nullptr) return 0;
    
    free (file->buffer);

    file->name     = nullptr;
    file->buffer   = nullptr;
    file->size     = 0;
    file->nStrings = 0;

    free (file);

    return nullptr;
}
