#include "list.h"

enum StatusCalloc
{
    OK_CALLOC    = 0,
    ERROR_CALLOC = 1,
};

static char*
GetElemCharPtr (Elem_t* elem);

static __m128i
GetElemM128i (Elem_t* elem);

static char*
GetElemCharPtr (Elem_t* elem)
{
    #ifdef UNION
        return elem->data.str;
    #else 
        return elem->data;
    #endif
}

static __m128i
GetElemM128i (Elem_t* elem)
{
    #ifdef UNION
        return elem->data.m128i;
    #else 
        return _mm_load_si128 ((__m128i*)elem->data);
    #endif
}

static StatusCalloc
ListStructRealloc (List *list);

////-----------------------------------------------/////

// Index_t
// ListFindElemString (List* list, 
//                     Elem_t elem);
// Index_t
// ListFindElemUnion  (List* list, 
//                     Elem_t elem);


// #ifdef UNION
//     Index_t ListFindElem (List* list, Elem_t elem) { return ListFindElemUnion (list, elem); }
// #else 
// /**
//  * string
//  * simple
//  * single
//  */
//     Index_t ListFindElem (List* list, Elem_t elem) { return ListFindElemString (list, elem); }
// #endif

////-------------------------------------///


List*
ListStructCtor ()
{
    List* list = (List*) calloc (1, sizeof (List));
    if (list == nullptr) return nullptr;

    list->capacity = List::LIST_INITIAL_CAPACITY;

    if (ListStructRealloc (list) == ERROR_CALLOC) 
    {
        free (list);
        return nullptr;
    }

    list->size = List::LIST_INITIAL_SIZE;

    for (size_t i = 0; i < List::LIST_INITIAL_CAPACITY; ++i)
    {
        // list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].length  = Elem::LEN_ELEM_POISON;
        list->data[i].nCopies = Elem::N_ELEM_POISON;
    }

    return list;
}

void 
ListStructDtor (List* list)
{
    if (list == nullptr) return;

    free (list->data);
    list->data     = nullptr;
    list->capacity = 0;
    list->size     = 0;

    free (list);
}

Index_t
ListInsert (List* list, Elem_t elem)
{
    assert (list);

    if (list->size >= list->capacity - 1) 
    {
        if (ListStructRealloc (list) == ERROR_CALLOC)
            return 0;
    } 

    list->data[list->size] = elem;
    list->size++;

    return (int)list->size - 1;
}

Index_t
ListFindElem (List* list, 
              Elem_t elem)
{
    assert (list);

    if (elem.length == 16) 
    {
        avx_t value = GetElemM128i (&elem);

        union 
        {
            __m128i m128i;
            size_t arr[2];
        } cmp;

        for (size_t i = 0; i < list->size; i++)
        { 
            cmp.m128i = value - GetElemM128i (&list->data[i]);
            if (cmp.arr[0] == 0 && cmp.arr[1] == 0)
            {
                return (int)i;
            }
        }

        return List::ELEM_NOT_FOUND;
    }

    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].length == elem.length && 
	        strncmp (GetElemCharPtr (&elem), GetElemCharPtr(&list->data[i]), (size_t)elem.length) == 0)
	    {
            return (int)i;
	    }
    }

    return List::ELEM_NOT_FOUND;
}

void 
ListStructDump (List* list)
{
    assert (list);

    printf ("LIST %p\n", list);
    printf ("capacity = %lu\n", list->capacity);
    printf ("size = %lu\n", list->size);

    printf ("\n\n");
    for (size_t i = 0; i < list->capacity; ++i)
    {
        printf ("%-3lu ", i);

        if (list->data[i].length != Elem::LEN_ELEM_POISON)
        {
            printf ("len = %-2d   ", list->data[i].length);
            printf ("nCopies = %-5d ", list->data[i].nCopies);
            printf ("%s", GetElemCharPtr (&list->data[i]));
        }
        else printf ("pn ");

        printf ("\n");
    }

    printf ("\n");
}

static StatusCalloc 
ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= List::LIST_EXPAND_MULTIPLIER;

    Elem_t* tmp = (Elem_t*) realloc (list->data, list->capacity * sizeof (Elem_t));
    if (tmp == nullptr) return ERROR_CALLOC;
    list->data = tmp;

    for (size_t i = list->capacity / List::LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        // list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].length  = Elem::LEN_ELEM_POISON;
        list->data[i].nCopies = Elem::N_ELEM_POISON;
    }

    return OK_CALLOC;
}
