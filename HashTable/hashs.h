#ifndef STL_hash_
#define STL_hash_

#include <limits.h>
#include "hashTable.h"

Hash_t HashReturn0        (HashData_t* data);
Hash_t HashLetterASCII    (HashData_t* data);
Hash_t HashStrlen         (HashData_t* data);
Hash_t HashSumLetterASCII (HashData_t* data);
Hash_t HashRor            (HashData_t* data);
Hash_t HashRol            (HashData_t* data);
Hash_t HashCRC32          (HashData_t* data);

#endif /* STL_hash_ */
