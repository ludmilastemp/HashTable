#include "list.h"

enum StatusCalloc
{
    OK_CALLOC    = 0,
    ERROR_CALLOC = 1,
};

#ifdef AVX // sse sse2 ssse3 mmx simd loadu 
static int
ListFindElem_avx (List* list,
                  avx_t value);
#endif

static StatusCalloc
ListStructRealloc (List *list);

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

#ifdef AVX
    if (elem.length == 16) return ListFindElem_avx (list, elem.data.m128i);
#endif

    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].length == elem.length && 
#ifdef AVX
            strncmp (elem.data.str, list->data[i].data.str, (size_t)elem.length) == 0)
#else 
	        strncmp (elem.data,     list->data[i].data,     (size_t)elem.length) == 0)
#endif
	    {

            return (int)i;
	    }
    }

    return List::ELEM_NOT_FOUND;
}

#ifdef AVX
static Index_t
ListFindElem_avx (List* list, avx_t value)
{
    assert (list);

    union 
    {
        __m128i m128i;
        size_t arr[2];
    } cmp;

    for (size_t i = 0; i < list->size; i++)
    {
        cmp.m128i = value - list->data[i].data.m128i; 
        if (cmp.arr[0] == 0 && cmp.arr[1] == 0)
	    {
            return (int)i;
	    }
    }

    return List::ELEM_NOT_FOUND;
}
#endif

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

            for (int j = 0; j < list->data[i].length; j++)
            {
#ifdef AVX
                printf ("%c", (list->data[i].data.str[j]));
#else 
                printf ("%c", (list->data[i].data[j]));
#endif
            }
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
