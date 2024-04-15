#include "hashTable.h"

// MM: int64_t hash_t
HashTable*
HashTableCtor (int /* M: size_t */ size, unsigned long long (*HashFunc)(ELEM_T data))
{
    // size == -1?
    HashTable* hashTable = (HashTable*) calloc (1, sizeof (HashTable));
    assert (hashTable); // M: error?

    hashTable->HashFunc    = HashFunc;
    hashTable->size        = size;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    hashTable->list = (List**) calloc ((size_t)size, sizeof (List*));
    assert (hashTable->list); // M: error?

    /**
     * Filling in the hash table header
     */
    for (int i = 0; i < size; i++)
    {
        hashTable->list[i] = ListStructCtor ();
        assert (hashTable->list[i]);
    }

    return hashTable;
}

int
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return 0;

    for (int i = 0; i < hashTable->size; i++)
        ListStructDtor (hashTable->list[i]);

    free (hashTable->list);
    
    hashTable->list        = nullptr;
    hashTable->HashFunc    = nullptr;
    hashTable->size        = 0;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    free (hashTable);

    return 0;
}

int
HashTableInsert (HashTable* hashTable, ELEM_T value, int lenElem)
{
    assert (hashTable);

    int indexList = abs(hashTable->HashFunc (value)) % hashTable->size; // M: size_t? capacity?
    
    assert (indexList >= 0);
    assert (indexList < hashTable->size);
    
    hashTable->nElem++;   

    int indexElem = ListFindElem (hashTable->list[indexList],
                                  value,
                                  lenElem);

    if (indexElem != List::ELEM_NOT_FOUND)    
                            /// const - fe
                            /// enum  - fe (ListFindElemReturn - ?)
                            /// const in struct
    {
        (hashTable->list[indexList]->data[indexElem].nElem)++;
        return indexList;
    }

    hashTable->nUniqueElem++;

    Elem elem = { .elem = value, .lenElem = lenElem, .nElem = 1 };
    ListInsert (hashTable->list[indexList], elem);

    return indexList;
}
        /// rename - ?
	// HashTableDumpListsToFile()
int HashTablePrintSize (HashTable* hashTable, const char* nameFile)
{
    assert (hashTable);
    assert (nameFile);

    FILE* fp = fopen (nameFile, "w");
    assert (fp); // M: error?

    for (int i = 0; i < hashTable->size; i++)
        fprintf (fp, "%d\n", hashTable->list[i]->size);

    fclose (fp);

    return 0;
}

int HashTableDump (HashTable* hashTable)
{
    assert (hashTable);
    
    printf ("\n\n!!!       HashTableDump      !!!\n");

    for (int i = 0; i < hashTable->size; i++)
    {
        printf ("list %d\n", i);
        if (hashTable->list[i]->size != 0)
        {
            ListStructDump (hashTable->list[i]);
            printf ("\n\n\n");
        }
    }

    printf ("\n");

    return 0;
}
