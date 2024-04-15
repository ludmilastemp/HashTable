#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include "tests/testProcess.h"
#include "plot/buildPlot.h"
#include <emmintrin.h>
                                       
int main (const int argc, const char** argv)
{
    if (argc == 1) return 0;

    if (argv[1][0] == '0')
    {                                         /// v< number of hash func
        BuildPlotAllHashTable ("plot/plotAll.py", 6, sizeHashTable);
        return 0;
    }

    File* file = FileProcess ("test.txt");
    assert (file);

    printf ("nStrings = %d\n", file->nStrings);

    unsigned long long (*hashArray[7])(ELEM_T data) = 
    {
        &HashReturn0,
        &HashLetterASCII,
        &HashStrlen,
        &HashSumLetterASCII,
        &HashRor,
        &HashRol,
        &Hash7
    };

    char nameFileWithResults[] = "tests/hash0.txt"; 
    char nameFileWithPlot[]    = "plot/plot0.py";

    int iArgc = 2;
    while (iArgc <= argc)
    {
        int nHashFunc = (argv[iArgc - 1][0] - '0');
        if (nHashFunc < 0 || nHashFunc > 7) break;
        iArgc++;

        printf ("\n\nnHashFunc = %d\n", nHashFunc);

        HashTable* hashTable = HashTableCtor (sizeHashTable, hashArray[nHashFunc - 1]);
        assert (hashTable);

        /**
         * Filling the hash table
         */
        int iBuf = 0;
        for (int i = 0; i < file->nStrings; i++)
        {
            int len = 16;
            if (file->buffer[iBuf + 16 - 1] != 0) len += 16;

            HashTableInsert (hashTable, file->buffer + iBuf, len);
            iBuf += len;
        }

        printf ("\n\n%d\n\n", hashTable->nUniqueElem);

        // HashTableDump (hashTable);

        sprintf (nameFileWithResults, "tests/hash%d.txt", nHashFunc);
        HashTablePrintSize (hashTable, nameFileWithResults); 
        
        sprintf (nameFileWithPlot, "plot/plot%d.py", nHashFunc);
        BuildPlotOneHashTable (nameFileWithPlot, hashTable);

        HashTableDtor (hashTable);
    }

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
