#ifndef STL_realize
#define STL_realize

// dataAccessors.h
// accessors.h
// your ideas!!! :DDDDDDDDDDDD

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>
#include "config.h" 

union Word
{
    avx_t avx; // Avx_t --> 
    char str[sizeWord];
};

#ifdef UNION
typedef Word Data_t;   
#else
typedef char Data_t[sizeWord];
#endif

inline char*
GetElemPtr (void* buffer, int nElem, int len)
{
#ifdef UNION
    return &((Data_t*)buffer)[nElem + len / sizeWord].str[len % sizeWord];
#else 
    return &((char*)buffer)[nElem * sizeWord + len];
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

inline avx_t
GetElemAvx (Data_t* data)
{
#ifdef UNION
    return data->avx;
#else 
    return _mm256_load_si256 ((avx_t*)data);
#endif
}


#endif /* STL_realize */