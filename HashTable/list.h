#ifndef STL_list_
#define STL_list_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "config.h" 

struct Elem
{
    Elem_t elem; // char* data 
    int    lenElem;  /// length
    int    nElem;       ///////// nCopies     
                
    // static constexpr Elem_t DATA_POISON     = { 0, nullptr };
    static const     int    LEN_ELEM_POISON = -1;
    static const     int    N_ELEM_POISON   = -1;      
};

typedef Elem List_t;

typedef int Index_t;

struct List
{
    List_t* data; // Elem_t

    size_t capacity;
    size_t size;

    static const int    ELEM_NOT_FOUND         = -1;
    static const size_t LIST_INITIAL_CAPACITY  = 4;
    static const size_t LIST_INITIAL_SIZE      = 0;
    static const size_t LIST_EXPAND_MULTIPLIER = 2;
};

    static const size_t LIST_INITIAL_CAPACITY  = 4;
    static const size_t LIST_INITIAL_SIZE      = 0;
    static const size_t LIST_EXPAND_MULTIPLIER = 2;
    
List*
ListStructCtor ();

int //???
ListStructDtor (List* list);

size_t // Index_t
ListInsert (List* list,
            List_t value); // Elem_t

int // Index_t
ListFindElem (List* list,
              Elem_t value,
              int lenElem);


// find(list, elem)
//

int
ListStructVerificator (List* list);

int // void
ListStructDump (List* list);

int
ListStructRealloc (List *list);

#endif /* STL_list_ */
