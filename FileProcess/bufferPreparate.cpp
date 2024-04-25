#include "bufferPreparate.h"

void
BufferPreparate (const char* fileName, struct File* file)
{
    assert (fileName);
    assert (file);

    char processFileName[100] = { 0 };
    sprintf (processFileName, "%s-process", fileName);

    file->name = processFileName;
    Fread (file);
    if (file->error == File::FILE_NOT_FOUND) 
    {
        File file_tmp = { .name = fileName };
        FileProcess (&file_tmp);

        if (file_tmp.error == File::FILE_NOT_FOUND) 
        {
            if (useDefaultText)
            {
                printf ("Used default text\n");
                BufferPreparate (defaultText, file);
            }
            else 
            {
                printf ("File not found!\n");
                Fclose (file);
            }

            Fclose (&file_tmp);
            return;
        }

        printf ("File process\n");
        Fprint (processFileName, &file_tmp);
        Fclose (&file_tmp);

        file->name = processFileName;
        Fread (file);
    }

    if (file->buffer == nullptr)
    {
        Fclose (file);
        return;
    }
}