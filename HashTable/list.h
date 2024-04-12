#ifndef STL_list_
#define STL_list_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define TOSTR(x) #x
#define LIST_DATA_PRINTF_SPECIFIER TOSTR(%c)

typedef const char* ELEM_T;     /// ctrl+h - ?

struct Elem
{
    ELEM_T elem;
    int    lenElem;
    int    nElem;       /// number of duplicate

    static constexpr ELEM_T DATA_POISON     = nullptr;
    static const     int    LEN_ELEM_POISON = -1;
    static const     int    N_ELEM_POISON   = -1;      
};

typedef Elem LIST_T;

struct List
{
    LIST_T* data;

    int capacity;
    int size;

    static const int ELEM_NOT_FOUND = -1;
};

static const int LIST_INITIAL_CAPACITY  = 4;
static const int LIST_INITIAL_SIZE      = 0;
static const int LIST_EXPAND_MULTIPLIER = 2;

List*
ListStructCtor ();

int
ListStructDtor (List* list);

int
ListInsert (List* list,
            LIST_T value);

int
ListFindElem (List* list,
              ELEM_T value,
              int lenElem);

int
ListStructVerificator (List* list);

int
ListStructDump (List* list);

int
ListStructRealloc (List *list);

#endif /* STL_list_ */
