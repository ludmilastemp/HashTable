#include "hashTable.h"

HashTable*
HashTableCtor (int size, int (*HashFunc)(ELEM_T data))
{
    HashTable* hashTable = (HashTable*) calloc (1, sizeof (HashTable));
    assert (hashTable);

    hashTable->HashFunc    = HashFunc;
    hashTable->size        = size;
    hashTable->nElem       = 0;
    hashTable->nUniqueElem = 0;

    hashTable->list = ListStructCtor ();
    assert (hashTable->list);

    Elem elem = { .elem     = List::DATA_POISON.elem,
                  .lenElem  = List::DATA_POISON.lenElem,
                  .nElem    = 0 };

    /**
     * Filling in the hash table header
     */
    for (int i = 0; i < size; i++)
    {
        ListInsert (hashTable->list, 0, elem);
    }

    return hashTable;
}

int
HashTableDtor (HashTable* hashTable)
{
    if (hashTable == nullptr) return 0;

    ListStructDtor (hashTable->list);

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
    int indexList = hashTable->HashFunc (value);
    hashTable->nElem++;   /// | ///
                          /// v ///
    int indexElem = ListFindInNElem (hashTable->list,
                                     hashTable->list->next[indexList],
                                     hashTable->list->data[indexList + 1].nElem,
                                     value,
                                     lenElem);

    if (indexElem != -1)    /// const - fe
                            /// enum  - fe (ListFindInNElemReturn - ?)
                            /// ?
    {
        (hashTable->list->data[indexElem].nElem)++;
        return indexList;
    }

    hashTable->nUniqueElem++;
    hashTable->list->data[indexList + 1].nElem++;

    Elem elem = { .elem = value, .lenElem = lenElem, .nElem = 1 };
    ListInsert (hashTable->list, indexList, elem);

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
        fprintf (fp, "%d\n", hashTable->list->data[i + 1].nElem);
    }

    fclose (fp);

    return 0;
}

int HashTableDump (HashTable* hashTable)
{
    printf ("\n\n!!!       HashTableDump      !!!\n");

    printf ("list  ");
    ListStructDump (hashTable->list);
    printf ("\n");

    printf ("\n");

    return 0;
}
