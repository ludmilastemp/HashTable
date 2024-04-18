#ifndef STL_list_
#define STL_list_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "config.h" 

typedef int Index_t;

struct Elem
{
    Data_t data;    // char*
    int    length;  
    int    nCopies;       
                
    // static constexpr Data_t DATA_POISON     = { 0, nullptr };
    static const     int    LEN_ELEM_POISON = -1;
    static const     int    N_ELEM_POISON   = -1;      
};

typedef Elem Elem_t;

struct List
{
    Elem_t* data;

    size_t capacity;
    size_t size;

    static const size_t LIST_INITIAL_CAPACITY  = 4;
    static const size_t LIST_INITIAL_SIZE      = 0;
    static const size_t LIST_EXPAND_MULTIPLIER = 2;
    static const int    ELEM_NOT_FOUND         = -1;
};
    
List*
ListStructCtor ();

void
ListStructDtor (List* list);

Index_t
ListInsert (List* list,
            Elem_t elem);

Index_t
ListFindElem (List* list,
              Elem_t elem);

void
ListStructDump (List* list);

#endif /* STL_list_ */
