#ifndef STL_config
#define STL_config

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>

typedef __m256i avx_t;
// typedef __m128i Wide_t SIMD_t???; Vector_t VectorData_t???

const size_t sizeHashTable = 911; // hashTableSize
const int    sizeWord = sizeof (avx_t); // vectorSize? hashTableWordSize??
    
#endif /* STL_config */