#include "list.h"

enum StatusCalloc_t
{
    OK_CALLOC    = 0,
    ERROR_CALLOC = 1,
};

static StatusCalloc_t ListStructRealloc (List *list);

static Index_t ListFindElemStrcmp (List* list, Data_t* data);
static Index_t ListFindElemAVX    (List* list, Data_t* data); 

#ifndef FIRST_OPTIMIZATION
Index_t ListFindElem (List* list, Data_t* data) { return ListFindElemStrcmp (list, data); }
#else 
Index_t ListFindElem (List* list, Data_t* data) { return ListFindElemAVX (list, data); }
#endif

void
ListStructCtor (List* list)
{
    assert (list);

    memset (list, 0, sizeof(List));
    list->capacity = List::LIST_INITIAL_CAPACITY;

    if (ListStructRealloc (list) == ERROR_CALLOC) 
    {
        return;
    }

    list->size = List::LIST_INITIAL_SIZE;

    for (size_t i = 0; i < List::LIST_INITIAL_CAPACITY; ++i)
    {
        list->data[i] = nullptr;
    }
}

void 
ListStructDtor (List* list)
{
    if (list == nullptr) return;

    free (list->data);
    list->data     = nullptr;
    list->capacity = 0;
    list->size     = 0;
}

Index_t
ListInsertElem (List* list, Data_t* data)
{
    assert (list);
    
    if (list->size >= list->capacity - 1) 
    {
        if (ListStructRealloc (list) == ERROR_CALLOC)
        {
            return 0;
        }
    } 

    list->data[list->size] = data;
    list->size++;

    return (int)list->size - 1;
}

static Index_t
ListFindElemStrcmp (List* list, 
                    Data_t* data)
{
    assert (list);
    assert (data);

    for (size_t i = 0; i < list->size; i++)
    {
        if (strncmp (GetElemCharPtr (data), GetElemCharPtr(list->data[i]), hashTableKeySize) == 0)
	    {
            return (int)i;
	    }
    }

    return List::ELEM_NOT_FOUND;
}

static Index_t
ListFindElemAVX (List* list, 
                 Data_t* data)
{
    assert (list);
    assert (data);

    Vector_t value = GetElemAvx (data);
    Vector_t mAll1 = _mm256_set1_epi16 ((short)0xffff);
    
    for (size_t i = 0; i < list->size; i++)
    { 
        if (_mm256_testz_si256 (value - GetElemAvx (list->data[i]), mAll1) == 1)
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

    // printf ("LIST %p\n", list);
    printf ("capacity = %lu\n", list->capacity);
    printf ("size = %lu\n", list->size);

    printf ("\n\n");
    for (size_t i = 0; i < list->capacity; ++i)
    {
        printf ("%-3lu ", i);

        if (GetElemCharPtr (list->data[i]) != nullptr)
        {
            printf ("%s", GetElemCharPtr (list->data[i]));
        }
        else 
        {
            printf ("pn ");
        }

        printf ("\n");
    }

    printf ("\n");
}

static StatusCalloc_t 
ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= List::LIST_EXPAND_MULTIPLIER;

    Elem_t** tmp = (Elem_t**) realloc (list->data, list->capacity * sizeof (Elem_t*));
    if (tmp == nullptr) return ERROR_CALLOC;
    list->data = tmp;

    for (size_t i = list->capacity / List::LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        list->data[i] = nullptr;
    }

    return OK_CALLOC;
}
