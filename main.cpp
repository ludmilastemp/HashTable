#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include <immintrin.h>
                                       
int main (const int argc, const char** argv)
{
    if (argc == 1) return 0;

//     size_t time1 = 0;
//     size_t time2 = 0;
// time1 = __rdtsc ();
// time2 = __rdtsc ();
// printf ("%lu\n", (time2 - time1));

    File* file = FileProcess ("test.txt");
    assert (file);

    // printf ("nStrings = %lu\n", file->nStrings);

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
        int iBuf = 0;
        for (size_t i = 0; i < file->nStrings; i++)
        {
            Elem_t elem = { 0 };
#ifdef BufferAsUnion
            int len = 1;
            if (file->words[iBuf].str[16 - 1] != 0) len++;
            iBuf += len;

            len *= 16;
            elem.data = file->words[iBuf];
#else 
            int len = 16;
            if (file->buffer[iBuf + 16 - 1] != 0) len += 16;
            iBuf += len;

            elem.data = file->buffer + iBuf;
#endif
            elem.length = len;

            HashTableInsert (hashTable, elem);
        }

        // printf ("\n\nnDuplicateElem = %lu\n\n", hashTable->nDuplicateElem);
        // printf ("\n\nnUniqueElem    = %lu\n\n", hashTable->nUniqueElem);
        
        //  HashTableDump (hashTable);

        HashTableDtor (hashTable);
    }

    size_t timeEnd = __rdtsc ();

    printf ("\n\ntime = %lu\n\n", (timeEnd - timeBegin) / 10000000);

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
