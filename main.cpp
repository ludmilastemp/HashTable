#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include <immintrin.h>
    
int main (const int argc, const char** argv)
{
    if (argc == 1) return 0; // user message???

    // File file_tmp = { .name = "text.txt" };
    // FileProcess (&file_tmp);
    // Fprint ("text.txt-process", &file_tmp);

    File file = { .name = "text.txt-process" };
    Fread (&file);
    assert (file.buffer); //errorrrrr???????

    printf ("buffer = %p\n", file.buffer); 

    HashFunc_t hashArray[] = 
    {
        &HashReturn0,
        &HashLetterASCII,
        &HashStrlen,
        &HashSumLetterASCII
        &HashRor,
        &HashRol,
        &HashCRC32
    };

    size_t timeBegin = __rdtsc ();

    int iArgc = 2; // for?? torchit + why 2???
    while (iArgc <= argc)
    {
        int hashFunc = (argv[iArgc - 1][0] - '0');
        if (hashFunc < 0 || hashFunc > sizeof (hashArray) / sizeof (HashFunc_t)) break;
        iArgc++;

        // printf ("\n\nnHashFunc = %d\n", hashFunc);

        HashTable hashTable = {};
        HashTableCtor (&hashTable, sizeHashTable, hashArray[hashFunc - 1]);

        /**
         * Filling the hash table
         */
        for (size_t i = 0; i < file.nStrings; i++)
        {
            HashTableInsert (&hashTable, &file.buffer[i]);
        }

        // printf ("nWords = %lu\n", hashTable.nUniqueElem);

        //  HashTableDump (&hashTable);

        HashTableDtor (&hashTable);
    }

    size_t timeEnd = __rdtsc ();

    printf ("\n\ntime = %lu\n\n", (timeEnd - timeBegin) / 1000000);

    Fclose (&file);

    printf ("Hello meow!\n\n");
}
