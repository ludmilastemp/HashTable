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

    File* file = STL_SplitFileIntoLines ("test.txt");
    assert (file);

    File* fileNew = BufferProcess (file);
    assert (fileNew);
    STL_Fclose (file);
    file = fileNew;

    unsigned long long (*hashArray[7])(ELEM_T data) = 
    {
        &Hash1,
        &Hash2,
        &Hash3,
        &Hash4,
        &Hash5,
        &Hash6,
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
            if (file->strings[i].str[16 - 1] != 0) len += 16;

            HashTableInsert (hashTable, file->buffer + iBuf, len);
            // HashTableInsert (hashTable, file->strings[i].str, len);

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
