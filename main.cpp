#include <stdio.h>
#include "FileProcess/fileProcess.h"
#include "HashTable/hashTable.h"
#include "HashTable/hashs.h"
#include <emmintrin.h>
                                          /// % in hash delete in func
int main (const int argc, const char** argv)
{
    File* file = STL_SplitFileIntoLines ("test.txt");
    assert (file);

    int nHashFunc = 1;
    if (argc != 1) nHashFunc = (argv[1][0] - '0');

    int (*HashFunc)(ELEM_T data) = nullptr;

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

    HashTableDump (hashTable);

    /**
     * Filling the hash table
     */
    for (int i = 0; i < file->nStrings; i++)
        HashTableInsert (hashTable, file->strings[i].str, file->strings[i].len);

    HashTableDump (hashTable);

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

    HashTableDtor (hashTable);

    STL_Fclose (file);

    printf ("Hello meow!\n\n");
}
