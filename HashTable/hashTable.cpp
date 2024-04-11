#include "hashTable.h"

HashTable*
HashTableCtor (int size, unsigned long long (*HashFunc)(ELEM_T data))
{
    HashTable* hashTable = (HashTable*) calloc (1, sizeof (HashTable));
    assert (hashTable);

    hashTable->HashFunc    = HashFunc;
    hashTable->size        = size;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    hashTable->list = (List**) calloc ((size_t)size, sizeof (List*));
    assert (hashTable->list);

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

    int indexList = abs((int)hashTable->HashFunc (value)) % hashTable->size;
    assert (indexList >= 0);
    assert (indexList < hashTable->size);
    
    hashTable->nElem++;   
                          /// | ///
                          /// v ///
    int indexElem = ListFindInNElem (hashTable->list[indexList],
                                     value,
                                     lenElem);

    if (indexElem != -1)    /// const - fe
                            /// enum  - fe (ListFindInNElemReturn - ?)
                            /// ?
    {
        (hashTable->list[indexList]->data[indexElem].nElem)++;
        return indexList;
    }

    hashTable->nUniqueElem++;
    // hashTable->list->data[indexList + 1].nElem++;

    Elem elem = { .elem = value, .lenElem = lenElem, .nElem = 1 };
    ListInsert (hashTable->list[indexList], 0, elem);

    return indexList;
}
        /// rename - ?
int HashTablePrintSize (HashTable* hashTable, const char* nameFile)
{
    assert (hashTable);
    assert (nameFile);

    FILE* fp = fopen (nameFile, "w");
    assert (fp);

    for (int i = 0; i < hashTable->size; i++)
    {
        fprintf (fp, "%d\n", hashTable->list[i]->size);
        // fprintf (fp, "%d\n", hashTable->list->data[i + 1].nElem);
    }

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
