#ifndef STL_hash_
#define STL_hash_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

const int sizeHashTable = 4013;
const int sizeWord = 16;

unsigned long long HashReturn0 (ELEM_T data);
unsigned long long HashLetterASCII (ELEM_T data);
unsigned long long HashStrlen (ELEM_T data);
unsigned long long HashSumLetterASCII (ELEM_T data);
unsigned long long HashRor (ELEM_T data);
unsigned long long HashRol (ELEM_T data);
unsigned long long Hash7 (ELEM_T data);


#endif /* STL_hash_ */
