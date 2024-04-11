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
};

typedef Elem LIST_T;

struct List
{
    LIST_T* data;
    // int*    next;
    // int*    prev;

    int capacity;
    int size;
    // int free;
               ///
    static constexpr LIST_T DATA_POISON = { nullptr, -1, -1};
    static const     int    PREV_POISON = -1;
};

enum ListError
{
    DATA_NULLPTR,
    NEXT_NULLPTR,
    PREV_NULLPTR,
    INCORRECT_CAPACITY,
    INCORRECT_SIZE,
    INCORRECT_FREE,
    INCORRECT_DATA_DATA,
    INCORRECT_NEXT_DATA,
    INCORRECT_PREV_DATA,
    FOUND_CYCLE,
    NO_SYMMETRY,
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
            int index,
            LIST_T value);

int
ListFindInNElem (List* list,
                 ELEM_T value,
                 int lenElem);

int
ListStructVerificator (List* list);

int
ListStructDump (List* list);

int
ListStructRealloc (List *list);

#endif /* STL_list_ */
