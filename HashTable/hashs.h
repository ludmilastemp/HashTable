#ifndef STL_hash_
#define STL_hash_

#include <limits.h>
#include "list.h"

typedef unsigned long long Hash_t;
typedef Data_t HashData_t;
typedef Hash_t (*HashFunc_t)(HashData_t* data);

Hash_t HashReturn0        (HashData_t* data);
Hash_t HashLetterASCII    (HashData_t* data);
Hash_t HashStrlen         (HashData_t* data);
Hash_t HashSumLetterASCII (HashData_t* data);
Hash_t HashRor            (HashData_t* data);
Hash_t HashRol            (HashData_t* data);
Hash_t HashCRC32          (HashData_t* data);

const HashFunc_t hashArray[] = 
{
    &HashReturn0,
    &HashLetterASCII,
    &HashStrlen,
    &HashSumLetterASCII,
    &HashRor,
    &HashRol,
    &HashCRC32
};

const char* const hashFuncDescription[] =
{
    "HashReturn0", 
    "HashLetterASCII", 
    "HashStrlen", 
    "HashSumLetterASCII", 
    "HashRor", 
    "HashRol", 
    "HashCRC32"
};

#endif /* STL_hash_ */
