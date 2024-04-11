#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include "tests/testProcess.h"
#include <emmintrin.h>
                                        /// % in hash delete in func
int main (const int argc, const char** argv)
{
    File* file = STL_SplitFileIntoLines ("test2.txt");
    assert (file);

    int nHashFunc = 1;
    if (argc != 1) nHashFunc = (argv[1][0] - '0');

    unsigned long long (*HashFunc)(ELEM_T data) = nullptr;

        /// array with ptr (��� ����� ���������, �� ����� ��� ������) // 
    switch (nHashFunc)
    {
        case 1: HashFunc = &Hash1; break;
        case 2: HashFunc = &Hash2; break;
        case 3: HashFunc = &Hash3; break;
        case 4: HashFunc = &Hash4; break;
        case 5: HashFunc = &Hash5; break;
        case 6: HashFunc = &Hash6; break;
        case 7: HashFunc = &Hash7; break;
        default: return 0;
    }

    HashTable* hashTable = HashTableCtor (sizeHashTable, HashFunc);
    assert (hashTable);

    // HashTableDump (hashTable);

    /**
     * Filling the hash table
     */
    for (int i = 0; i < file->nStrings; i++)
    {
        //  printf ("i = %d\n", i);
        HashTableInsert (hashTable, file->strings[i].str, file->strings[i].len);
    }

    //return 0;

    // HashTableDump (hashTable);

    const char* nameFileWithResults = nullptr;
    switch (nHashFunc)
    {
        case 1: nameFileWithResults = "tests/hash1.txt"; break;
        case 2: nameFileWithResults = "tests/hash2.txt"; break;
        case 3: nameFileWithResults = "tests/hash3.txt"; break;
        case 4: nameFileWithResults = "tests/hash4.txt"; break;
        case 5: nameFileWithResults = "tests/hash5.txt"; break;
        case 6: nameFileWithResults = "tests/hash6.txt"; break;
        case 7: nameFileWithResults = "tests/hash7.txt"; break;
        default: return 0;
    }       /// copypasta too

    HashTablePrintSize (hashTable, nameFileWithResults); 
    
    const char* nameFileWithPlot = nullptr;
    switch (nHashFunc)
    {
        case 1: nameFileWithPlot = "plot/plot1.py"; break;
        case 2: nameFileWithPlot = "plot/plot2.py"; break;
        case 3: nameFileWithPlot = "plot/plot3.py"; break;
        case 4: nameFileWithPlot = "plot/plot4.py"; break;
        case 5: nameFileWithPlot = "plot/plot5.py"; break;
        case 6: nameFileWithPlot = "plot/plot6.py"; break;
        case 7: nameFileWithPlot = "plot/plot7.py"; break;
        default: return 0;
    }       /// copypasta too

    TestProcessOneHashTable (nameFileWithPlot, hashTable);

    HashTableDtor (hashTable);

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
