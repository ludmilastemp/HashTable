#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include <immintrin.h>
                
int main (const int argc, const char** argv)
{
    if (argc == 1) return 0;

    File* file = FileProcess ("test.txt");
    assert (file);

    // printf ("buffer = %p\n", file->words); 

    HashFunc_t hashArray[nHashFunc] = 
    {
        &HashReturn0,
        &HashLetterASCII,
        &HashStrlen,
        &HashSumLetterASCII,
        &HashRor,
        &HashRol
    };

    size_t timeBegin = __rdtsc ();

    int iArgc = 2;
    while (iArgc <= argc)
    {
        int hashFunc = (argv[iArgc - 1][0] - '0');
        if (hashFunc < 0 || hashFunc > nHashFunc) break;
        iArgc++;

        // printf ("\n\nnHashFunc = %d\n", hashFunc);

        HashTable* hashTable = HashTableCtor (sizeHashTable, hashArray[hashFunc - 1]);
        assert (hashTable);

        /**
         * Filling the hash table
         */
        // int i = 0;
        for (size_t i = 0; i < file->nStrings; i++)
        {
            HashTableInsert (hashTable, &file->words[i]);
        }

        //  HashTableDump (hashTable);

        HashTableDtor (hashTable);
    }

    size_t timeEnd = __rdtsc ();

    printf ("\n\ntime = %lu\n\n", (timeEnd - timeBegin) / 10000000);

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
