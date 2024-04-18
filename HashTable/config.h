#ifndef STL_config
#define STL_config

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>

#ifdef AVX
    typedef __m128i avx_t; 

    union Word
    {
        avx_t m128i;
        char str[16];
    };
#endif

#ifdef AVX
typedef Word Data_t;   
#else
typedef char* Data_t;
#endif

typedef unsigned long long Hash_t;
typedef char* HashData_t;

const size_t sizeHashTable = 403;
const int    sizeWord  = sizeof (__m128i);
const int    nHashFunc = 6; // fe

#endif /* STL_config */