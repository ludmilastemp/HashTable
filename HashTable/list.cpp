#include "list.h"

enum StatusCalloc
{
    OK_CALLOC    = 0,
    ERROR_CALLOC = 1,
};

static StatusCalloc
ListStructRealloc (List *list);

////-----------------------------------------------/////

// Index_t
// ListFindElemString (List* list, 
//                     Data_t data);
// Index_t
// ListFindElemUnion  (List* list, 
//                     Data_t data);


// #ifdef UNION
//     Index_t ListFindElem (List* list, Data_t data) { return ListFindElemUnion (list, elem); }
// #else 
// /**
//  * string
//  * simple
//  * single
//  */
//     Index_t ListFindElem (List* list, Data_t data) { return ListFindElemString (list, elem); }
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
        // list->data[i].nCopies = Elem::N_ELEM_POISON;
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
ListInsert (List* list, Data_t* data)
{
    assert (list);

    if (list->size >= list->capacity - 1) 
    {
        if (ListStructRealloc (list) == ERROR_CALLOC)
            return 0;
    } 

    list->data[list->size] = data;
    list->size++;

    return (int)list->size - 1;
}

Index_t
ListFindElem (List* list, 
              Data_t* data)
{
    assert (list);

    if (1) 
    {
        avx_t value = GetElemAvx (data);

        union 
        {
            avx_t avx;
            size_t arr[sizeWord / sizeof (size_t)];
        } cmp;

        for (size_t i = 0; i < list->size; i++)
        { 
            cmp.avx = value - GetElemAvx (list->data[i]);
            if (cmp.arr[0] == 0 && cmp.arr[1] == 0 && ////////
                cmp.arr[2] == 0 && cmp.arr[3] == 0)
            {
                return (int)i;
            }
        }

        return List::ELEM_NOT_FOUND;
    }

    for (size_t i = 0; i < list->size; i++)
    {
        if (strncmp (GetElemCharPtr (data), GetElemCharPtr(list->data[i]), sizeWord) == 0)
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

        // if (list->data[i].nCopies != Elem::N_ELEM_POISON)
        {
            printf ("%s", GetElemCharPtr (list->data[i]));
        }
        // else printf ("pn ");

        printf ("\n");
    }

    printf ("\n");
}

static StatusCalloc 
ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= List::LIST_EXPAND_MULTIPLIER;

    Elem_t** tmp = (Elem_t**) realloc (list->data, list->capacity * sizeof (Elem_t*));
    if (tmp == nullptr) return ERROR_CALLOC;
    list->data = tmp;

    for (size_t i = list->capacity / List::LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        // list->data[i].elem    = Elem::DATA_POISON;
        // list->data[i].nCopies = Elem::N_ELEM_POISON;
    }

    return OK_CALLOC;
}
