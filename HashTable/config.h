#ifndef STL_config
#define STL_config

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>

    typedef __m128i avx_t; 
    
// #ifdef AVX // sse sse2 ssse3 mmx simd loadu 
#ifdef UNION

    union Word
    {
        avx_t m128i;
        char str[16];
    };
#endif

#ifdef UNION
typedef Word Data_t;   
#else
typedef char* Data_t;
#endif

typedef unsigned long long Hash_t;
typedef Data_t HashData_t;

const size_t sizeHashTable = 403;
const int    sizeWord  = sizeof (__m128i);

#endif /* STL_config */