#ifndef STL_hash_table_
#define STL_hash_table_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "hashs.h"

typedef Hash_t (*HashFunc_t)(HashData_t data); ///////////

struct HashTable
{
    List** list; // !!!
    
    //Hash_t (*HashFunc)(HashData_t data);
    HashFunc_t HashFunc;

    size_t capacity;
    size_t nElem;              // number of elem with duplicate
    size_t nUniqueElem;
};

HashTable*
HashTableCtor (size_t capacity,
               Hash_t (*HashFunc)(HashData_t data));

int //?
HashTableDtor (HashTable* hashTable);

size_t //?
HashTableInsert (HashTable* hashTable,
                 Elem_t value,
                 int lenElem);

int //?
HashTableDumpListsToFile (HashTable* hashTable,
                          const char* nameFile);

int //?
HashTableDump (HashTable* hashTable);

#endif /* STL_hash_table_ */
