#ifndef STL_dataAccessors
#define STL_dataAccessors

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>
#include "config.h" 

union Word
{
    Vector_t avx;  
    char str[hashTableKeySize];
};

#ifdef UNION
typedef Word Data_t;   
#else
typedef char Data_t[hashTableKeySize];
#endif

inline char*
GetElemPtr (void* buffer, int nElem, int len)
{
#ifdef UNION
    return &((Data_t*)buffer)[nElem + len / hashTableKeySize].str[len % hashTableKeySize];
#else 
    return &((char*)buffer)[nElem * hashTableKeySize + len];
#endif
}

inline char*
GetElemCharPtr (Data_t* data)
{
#ifdef UNION
    return data->str;
#else 
    return (char*)data;
#endif
}

inline Vector_t
GetElemAvx (Data_t* data)
{
#ifdef UNION
    return data->avx;
#else 
    return _mm256_load_si256 ((Vector_t*)data);
#endif
}


#endif /* STL_dataAccessors */