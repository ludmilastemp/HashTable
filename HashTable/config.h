#ifndef STL_config
#define STL_config

#include <immintrin.h>
#include <emmintrin.h>
#include <nmmintrin.h>

typedef __m256i Vector_t; 

const size_t hashTableSize    = 911; 
const int    hashTableKeySize = sizeof (Vector_t); 
const bool   useDefaultText   = true;
const char   defaultText[]    = "text.txt";
const int    nMeasurements    = 3;
const bool   measurements     = false;
    
#endif /* STL_config */