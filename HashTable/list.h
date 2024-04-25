#ifndef STL_list_
#define STL_list_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "config.h" 
#include "dataAccessors.h" 

typedef int Index_t;
typedef Data_t Elem_t;

struct List
{
    Elem_t** data; // fe // Elem_t** or memcpy - ???

    size_t capacity;
    size_t size;

    static const size_t LIST_INITIAL_CAPACITY  = 4;
    static const size_t LIST_INITIAL_SIZE      = 0;
    static const size_t LIST_EXPAND_MULTIPLIER = 2;
    static const int    ELEM_NOT_FOUND         = -1;
};
    
void ListStructCtor (List* list);
void ListStructDtor (List* list);

Index_t ListInsertElem (List* list, Data_t* data);
Index_t ListFindElem   (List* list, Data_t* data);

void ListStructDump (List* list);

#endif /* STL_list_ */
