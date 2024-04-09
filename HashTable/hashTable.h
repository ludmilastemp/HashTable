#ifndef STL_hash_table_
#define STL_hash_table_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct HashTable
{
    List* list;
    int (*HashFunc)(ELEM_T data);
    int size;
    int nElem;              // number of elem with duplicate
    int nUniqueElem;
};

HashTable*
HashTableCtor (int size,
               int (*HashFunc)(ELEM_T data));

int
HashTableDtor (HashTable* hashTable);

int
HashTableInsert (HashTable* hashTable,
                 ELEM_T value,
                 int lenElem);

int
HashTablePrintSize (HashTable* hashTable,
                    const char* nameFile);

int
HashTableDump (HashTable* hashTable);

#endif /* STL_hash_table_ */
