#include "hashTable.h"

void
HashTableCtor (HashTable* hashTable, 
               size_t nLists, 
               HashFunc_t HashFunc)
{
    assert (hashTable);

    memset (hashTable, 0, sizeof(HashTable));

    hashTable->hashFunc        = HashFunc;
    hashTable->nLists          = nLists;
    hashTable->nDuplicateElems = 0;
    hashTable->nUniqueElems    = 0;

    /**
     * Fill hash table header
     */
    {
        hashTable->lists = (List*) calloc (nLists, sizeof (List));
        if (hashTable->lists == nullptr) return;

        for (size_t i = 0; i < nLists; i++)
        {
            ListStructCtor (&hashTable->lists[i]);
        }
    }
}

void 
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return;

    for (size_t i = 0; i < hashTable->nLists; i++)
    {
        ListStructDtor (&hashTable->lists[i]);
    }

    free (hashTable->lists);
    
    hashTable->lists           = nullptr;
    hashTable->hashFunc        = nullptr;
    hashTable->nLists          = 0;
    hashTable->nDuplicateElems = 0;
    hashTable->nUniqueElems    = 0;
}

Index_t 
HashTableInsert (HashTable* hashTable, 
                 Data_t* data)
{
    assert (hashTable);
    assert (data);
    
    Index_t indexList = (Index_t)(hashTable->hashFunc (data) % hashTable->nLists); 
    hashTable->nDuplicateElems++;   

    int indexElem = ListFindElem (&hashTable->lists[indexList], data);

    if (indexElem == List::ELEM_NOT_FOUND)    
    {
        hashTable->nUniqueElems++;
        ListInsertElem (&hashTable->lists[indexList], data);
    }

    return indexList;
}

void 
HashTableDumpListsToFile (HashTable* hashTable, 
                          int nHashFunc)
{
    assert (hashTable);

    char fileDumpName[100] = { 0 };
    sprintf (fileDumpName, "Distribution/%s.txt", hashFuncDescription[nHashFunc]);

    FILE* fp = fopen (fileDumpName, "w");
    if (fp == nullptr) return; 

    for (size_t i = 0; i < hashTable->nLists; i++)
    {
        fprintf (fp, "%lu\n", hashTable->lists[i].size);
    }

    fclose (fp);
}

void 
HashTableDump (HashTable* hashTable)
{
    assert (hashTable);
    
    printf ("\n\n!!!       HashTableDump      !!!\n");

    for (size_t i = 0; i < hashTable->nLists; i++)
    {
        printf ("list %lu\n", i);                      
        if (hashTable->lists[i].size != 0)
        {
            ListStructDump (&hashTable->lists[i]);
            printf ("\n\n\n");
        }
    }

    printf ("\n");
}
