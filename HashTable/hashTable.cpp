#include "hashTable.h"

HashTable*
HashTableCtor (size_t capacity, Hash_t (*HashFunc)(HashData_t data))
{
    HashTable* hashTable = (HashTable*) calloc (1, sizeof (HashTable));
    if (hashTable == nullptr) return nullptr;

    hashTable->HashFunc    = HashFunc;
    hashTable->capacity    = capacity;
    hashTable->nDuplicateElem       = 0;
    hashTable->nUniqueElem = 0;

    hashTable->list = (List**) calloc (capacity, sizeof (List*));
    if (hashTable->list == nullptr) return nullptr;

    /**
     * Filling in the hash table header
     */
    for (size_t i = 0; i < capacity; i++)
    {
        hashTable->list[i] = ListStructCtor ();
        if (hashTable->list[i] == nullptr)
        {
            for (size_t j = 0; j < i; j++)
            {
                free (hashTable->list[j]);
            }
            free (hashTable);
            return nullptr;
        }
    }

    return hashTable;
}

void 
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return;

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        ListStructDtor (hashTable->list[i]);
    }

    free (hashTable->list);
    
    hashTable->list           = nullptr;
    hashTable->HashFunc       = nullptr;
    hashTable->capacity       = 0;
    hashTable->nDuplicateElem = 0;
    hashTable->nUniqueElem    = 0;

    free (hashTable);
}

Index_t 
HashTableInsert (HashTable* hashTable, 
                 Elem_t elem)
{
    assert (hashTable);
    
    size_t indexList = hashTable->HashFunc (elem.data) % hashTable->capacity; 
    hashTable->nDuplicateElem++;   

    int indexElem = ListFindElem (hashTable->list[indexList],
                                  elem);

    if (indexElem != List::ELEM_NOT_FOUND)    
    {
        (hashTable->list[indexList]->data[indexElem].nCopies)++;
        return (int)indexList;
    }

    hashTable->nUniqueElem++;

    elem.nCopies = 1;
    ListInsert (hashTable->list[indexList], elem);

    return (int)indexList;
}

void 
HashTableDumpListsToFile (HashTable* hashTable, const char* nameFile)
{
    assert (hashTable);
    assert (nameFile);

    FILE* fp = fopen (nameFile, "w");
    if (fp == nullptr) return; 

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        fprintf (fp, "%lu\n", hashTable->list[i]->size);
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
        if (hashTable->list[i]->size != 0)
        {
            ListStructDump (hashTable->list[i]);
            printf ("\n\n\n");
        }
    }

    printf ("\n");
}
