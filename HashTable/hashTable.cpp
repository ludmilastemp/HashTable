#include "hashTable.h"

void
HashTableCtor (HashTable* hashTable, 
               size_t capacity, 
               HashFunc_t HashFunc)
{
    assert (hashTable);

    // LIFE HOOK: memset( hashTable, sizeof(HashTable), 0);
    hashTable->HashFunc       = HashFunc;
    hashTable->capacity       = capacity;
    hashTable->nDuplicateElem = 0;
    hashTable->nUniqueElem    = 0;


    /**
     * Filling in the hash table header
     * ? Fill hash table header
     */
    {
        hashTable->list = (List*) calloc (capacity, sizeof (List));
        if (hashTable->list == nullptr) return;

        for (size_t i = 0; i < capacity; i++)
        {
            ListStructCtor (&hashTable->list[i]);
        }
    }
}

void 
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return;

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        ListStructDtor (&hashTable->list[i]);
    }

    free (hashTable->list);
    
    hashTable->list           = nullptr;
    hashTable->HashFunc       = nullptr;
    hashTable->capacity       = 0;
    hashTable->nDuplicateElem = 0;
    hashTable->nUniqueElem    = 0;
}

Index_t 
HashTableInsert (HashTable* hashTable, 
                 Data_t* data)
{
    assert (hashTable);
    assert (data);
    
    Index_t indexList = (Index_t)(hashTable->HashFunc (data) % hashTable->capacity); 
    hashTable->nDuplicateElem++;   

    int indexElem = ListFindElem (&hashTable->list[indexList], data);

    if (indexElem == List::ELEM_NOT_FOUND)    
    {
        hashTable->nUniqueElem++;
        ListInsert (&hashTable->list[indexList], data);
    }

    return indexList;
}

void 
HashTableDumpListsToFile (HashTable* hashTable, 
                          const char* nameFile)
{
    assert (hashTable);
    assert (nameFile);

    FILE* fp = fopen (nameFile, "w");
    if (fp == nullptr) return; 

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        fprintf (fp, "%lu\n", hashTable->list[i].size);
    }

    fclose (fp);
}

void 
HashTableDump (HashTable* hashTable)
{
    assert (hashTable);
    
    printf ("\n\n!!!       HashTableDump      !!!\n");

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        printf ("list %lu\n", i);                      
        if (hashTable->list[i].size != 0)
        {
            ListStructDump (&hashTable->list[i]);
            printf ("\n\n\n");
        }
    }

    printf ("\n");
}
