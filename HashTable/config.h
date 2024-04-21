#ifndef STL_config
#define STL_config

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>

typedef __m256i avx_t; 

const size_t sizeHashTable = 403;
const int    sizeWord = sizeof (avx_t);
    
// #ifdef AVX // sse sse2 ssse3 mmx simd loadu 


#endif /* STL_config */