#ifndef STL_hash_table_
#define STL_hash_table_

#include "list.h"
#include "hashs.h"

struct HashTable
{
    size_t nLists;
    List* lists; 
    
    HashFunc_t hashFunc;

    size_t nDuplicateElems;
    size_t nUniqueElems;    
};

void HashTableCtor (HashTable* HashTable, size_t nLists, HashFunc_t HashFunc);
void HashTableDtor (HashTable* hashTable);

Index_t HashTableInsert (HashTable* hashTable, Data_t* data);

void HashTableDumpListsToFile (HashTable* hashTable, int nHashFunc); 
void HashTableDump (HashTable* hashTable);

#endif /* STL_hash_table_ */
