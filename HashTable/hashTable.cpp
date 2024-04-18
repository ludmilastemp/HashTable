#include "hashTable.h"

HashTable*
HashTableCtor (size_t capacity, Hash_t (*HashFunc)(HashData_t data))
{
    HashTable* hashTable = (HashTable*) calloc (1, sizeof (HashTable));
    if (hashTable == nullptr) return nullptr;

    hashTable->HashFunc    = HashFunc;
    hashTable->capacity    = capacity;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    hashTable->list = (List**) calloc (capacity, sizeof (List*));
    if (hashTable->list == nullptr) return nullptr;

    /**
     * Filling in the hash table header
     */
    for (size_t i = 0; i < capacity; i++)
    {
        hashTable->list[i] = ListStructCtor ();
        assert (hashTable->list[i]); // correct error handling free all calloc-ed
    }

    return hashTable;
}

int 
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return 0;

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        ListStructDtor (hashTable->list[i]);
    }

    free (hashTable->list);
    
    hashTable->list        = nullptr;
    hashTable->HashFunc    = nullptr;
    hashTable->capacity    = 0;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    free (hashTable);

    return 0;
}

size_t 
HashTableInsert (HashTable* hashTable, Elem_t value, int lenElem)
{
    assert (hashTable);
    
#ifdef AVX
    size_t indexList = hashTable->HashFunc (value.str) % hashTable->capacity; 
#else 
    size_t indexList = hashTable->HashFunc (value) % hashTable->capacity; 
#endif

    hashTable->nElem++;   

    int indexElem = ListFindElem (hashTable->list[indexList],
                                  value,
                                  lenElem);

    if (indexElem != List::ELEM_NOT_FOUND)    
    {
        (hashTable->list[indexList]->data[indexElem].nElem)++;
        return indexList;
    }

    hashTable->nUniqueElem++;

    Elem elem = { .elem = value, .lenElem = lenElem, .nElem = 1 };
    ListInsert (hashTable->list[indexList], elem);

    return indexList;
}

int 
HashTableDumpListsToFile (HashTable* hashTable, const char* nameFile)
{
    assert (hashTable);
    assert (nameFile);

    FILE* fp = fopen (nameFile, "w");
    if (fp == nullptr) return 0; 

    for (size_t i = 0; i < hashTable->capacity; i++)
    {
        fprintf (fp, "%lu\n", hashTable->list[i]->size);
    }

    fclose (fp);

    return 0;
}

int 
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

    return 0;
}
