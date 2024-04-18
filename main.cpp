#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
// #include "tests/testProcess.h"
// #include "plot/buildPlot.h"
#include <immintrin.h>
                                       
int main (const int argc, const char** argv)
{
    if (argc == 1) return 0;

    size_t time1 = 0;
    size_t time2 = 0;
time1 = __rdtsc ();
time2 = __rdtsc ();
printf ("%lu\n", (time2 - time1));

    if (argv[1][0] == '0')
    {                                         
    //     BuildPlotAllHashTable ("plot/plotAll.py", nHashFunc);
        return 0;
    }

    File* file = FileProcess ("test_dbg.txt");
    // File* file = FileProcess ("test.txt");
    assert (file);

    printf ("nStrings = %lu\n", file->nStrings);

    Hash_t (*hashArray[nHashFunc])(HashData_t data) = 
    {
        &HashReturn0,
        &HashLetterASCII,
        &HashStrlen,
        &HashSumLetterASCII,
        &HashRor,
        &HashRol
    };

    size_t timeBegin = __rdtsc ();
//     size_t time1 = 0;
//     size_t time2 = 0;

// time1 = __rdtsc ();
// time2 = __rdtsc ();

//     printf ("time = %lu\n", (time2 - time1) / 10000000);

    int iArgc = 2;
    while (iArgc <= argc)
    {
        int hashFunc = (argv[iArgc - 1][0] - '0');
        if (hashFunc < 0 || hashFunc > nHashFunc) break;
        iArgc++;

        printf ("\n\nnHashFunc = %d\n", hashFunc);

        HashTable* hashTable = HashTableCtor (sizeHashTable, hashArray[hashFunc - 1]);
        assert (hashTable);

        /**
         * Filling the hash table
         */
        int iBuf = 0;
        for (size_t i = 0; i < file->nStrings; i++)
        {
#ifdef AVX
            int len = 1;
            if (file->words[iBuf].str[16 - 1] != 0) len++;

            HashTableInsert (hashTable, file->words[iBuf], len * 16);
            iBuf += len;
#else 
            int len = 16;
            if (file->buffer[iBuf + 16 - 1] != 0) len += 16;

            HashTableInsert (hashTable, file->buffer + iBuf, len);
            iBuf += len;
#endif
        }

        printf ("\n\n%lu\n\n", hashTable->nUniqueElem);

        //  HashTableDump (hashTable);

        // char nameFileWithResults[] = "tests/hash0.txt"; 
        // sprintf (nameFileWithResults, "tests/hash%d.txt", hashFunc);
        // HashTableDumpListsToFile (hashTable, nameFileWithResults); 
        
        // char nameFileWithPlot[]    = "plot/plot0.py";
        // sprintf (nameFileWithPlot, "plot/plot%d.py", hashFunc);
        // BuildPlotOneHashTable (nameFileWithPlot, hashTable);

        HashTableDtor (hashTable);
    }

    size_t timeEnd = __rdtsc ();

    printf ("\n\ntime = %lu\n\n", (timeEnd - timeBegin) / 10000000);

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
