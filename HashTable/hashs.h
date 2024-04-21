#ifndef STL_hash_
#define STL_hash_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>
#include "list.h"
         
const int nHashFunc = 6; 

Hash_t HashReturn0        (HashData_t data);
Hash_t HashLetterASCII    (HashData_t data);
Hash_t HashStrlen         (HashData_t data);
Hash_t HashSumLetterASCII (HashData_t data);
Hash_t HashRor            (HashData_t data);
Hash_t HashRol            (HashData_t data);
Hash_t Hash7              (HashData_t data);


#endif /* STL_hash_ */
