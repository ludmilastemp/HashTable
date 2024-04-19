#ifndef STL_hash_table_
#define STL_hash_table_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "hashs.h"

typedef Hash_t (*HashFunc_t)(HashData_t data);

struct HashTable
{
    List** list; // !!!
    
    HashFunc_t HashFunc;

    size_t capacity;
    size_t nDuplicateElem;  
    size_t nUniqueElem;
};

HashTable*
HashTableCtor (size_t capacity,
               HashFunc_t HashFunc);

void
HashTableDtor (HashTable* hashTable);

Index_t
HashTableInsert (HashTable* hashTable,
                 Elem_t elem);

void
HashTableDumpListsToFile (HashTable* hashTable,
                          const char* nameFile);

void
HashTableDump (HashTable* hashTable);

#endif /* STL_hash_table_ */
