#include "fileProcess.h"

static int  CountNumberOfLines (char* buffer, size_t size);
static void SplitIntoLines (struct File* file);

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

File* STL_SplitFileIntoLines (const char* nameFile)
{
    assert (nameFile);

    File* file = STL_Fread (nameFile);

    file->nStrings = CountNumberOfLines (file->buffer, file->size);

    file->strings = (String*) calloc ((size_t)file->nStrings, sizeof (String));
    assert (file->strings);

    SplitIntoLines (file);

    printf ("nStrings = %d\n", file->nStrings);
    return file;
}

static int CountNumberOfLines (char* buffer, size_t size)
{
    int numberOfLines = 0;

    char* ptr = buffer;
    while (ptr != buffer + size - 1)
    {                               ///  && !isalpha ()) |
        while (ptr != buffer + size - 1)            /// <-
        {
            if (isalpha (*ptr))
            {
                numberOfLines++;
                break;
            }
            ptr++;
        }
                                    ///  &&  isalpha ()) |
        while (ptr != buffer + size - 1)            /// <-
        {
            if (isalpha (*ptr)) ptr++;
            else break;
        }
    }

    return numberOfLines;
}
                                 /// copypasta us !!!realloc!!! - ?
static void SplitIntoLines (File* file)
{
    assert (file);

    char* ptr = file->buffer;

    for (int line = 0; line < file->nStrings; line++)
    {
        while (ptr != file->buffer + file->size - 1)
        {
            if (('a' <= *ptr && *ptr <= 'z') ||
                ('A' <= *ptr && *ptr <= 'Z'))
                break;
            ptr++;
        }

        (file->strings + line)->str = ptr;

        while (ptr != file->buffer + file->size - 1)
        {
            if (('a' <= *ptr && *ptr <= 'z') ||
                ('A' <= *ptr && *ptr <= 'Z'))
                ptr++;
            else break;
        }

        (file->strings + line)->len = (int)(ptr - (file->strings + line)->str);
    }
}

int STL_Fclose (struct File* file)
{
    free (file->buffer);
    free (file->strings);

    file->name     = nullptr;
    file->buffer   = nullptr;
    file->size     = 0;
    file->nStrings = 0;
    file->strings  = nullptr;

    free (file);

    return 0;
}

