#ifndef STL_hash_table_
#define STL_hash_table_

#include "list.h"

typedef unsigned long long Hash_t;
typedef Data_t HashData_t;
typedef Hash_t (*HashFunc_t)(HashData_t* data);

struct HashTable
{
    size_t capacity; // n_lists nLists
    List* list; // lists, list_array, chains
    
    HashFunc_t HashFunc; // hashFunc 

    size_t nDuplicateElem; // nDuplicatedElem___s____  
    size_t nUniqueElem;    // --//--
};

void HashTableCtor (HashTable* HashTable, size_t capacity, HashFunc_t HashFunc);
void HashTableDtor (HashTable* hashTable);

Index_t HashTableInsert (HashTable* hashTable, Data_t* data);

// size of word --> word size
// name of file --> file name 
void HashTableDumpListsToFile (HashTable* hashTable, const char* nameFile); // fileName
void HashTableDump (HashTable* hashTable);

#endif /* STL_hash_table_ */
