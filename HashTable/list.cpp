#include "list.h"

#ifdef AVX // sse sse2 ssse3 mmx simd loadu 
static int
ListFindElem_avx (List* list,
                  avx_t value);
#endif

List*
ListStructCtor ()
{
    List* list = (List*) calloc (1, sizeof (List));
    if (list == nullptr) return nullptr;

    list->capacity = LIST_INITIAL_CAPACITY;

    ListStructRealloc (list); // error

    list->size = LIST_INITIAL_SIZE;

    for (size_t i = 0; i < LIST_INITIAL_CAPACITY; ++i)
    {
        // list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].lenElem = Elem::LEN_ELEM_POISON;
        list->data[i].nElem   = Elem::N_ELEM_POISON;
    }

    return list;
}

int 
ListStructDtor (List* list)
{
    if (list == nullptr) return 0;

    free (list->data);
    list->data     = nullptr;
    list->capacity = 0;
    list->size     = 0;

    free (list);

    return 0;
}

size_t
ListInsert (List* list, List_t value)
{
    assert (list);

    if (list->size >= list->capacity - 1) ListStructRealloc (list); // error

    list->data[list->size] = value;
    list->size++;

    return list->size - 1;
}

//ListFindElemSSE3
//ListFindElemAVX
//ListFindElemSingle

// #define ListFindElem ListFindElemSSE3

// #ifdef ...
// int ListFindElem() { return ListFindtFindElem ListFindEleElemAVX(...); }
// int ListFindElem() { return ListFindElemSSE3(...); }
// int ListFindElem() { return ListFindElemSingle(...); }


int
ListFindElem (List* list, Elem_t value, int lenElem)
{
    assert (list);

#ifdef AVX
    // if (lenElem == 16) return ListFindElem_avx (list, value.m128i);

    // lenElem == 32
    // -> в отдельную функцию полностью под ifdef обе функции и одинаковые названияя
#endif
/// функция compare и ее под ifdef (на крайняк копипаста цикла не так плохо)

    for (size_t i = 0; i < list->size; i++)
    {
        if (list->data[i].lenElem == lenElem && 
            //Compare()
#ifdef AVX
            strncmp (value.str, list->data[i].elem.str, (size_t)lenElem) == 0)
#else 
// load
// _mm_loadu_si128 (потом без u (да да, ищи выравнивание))
	        strncmp (value, list->data[i].elem, (size_t)lenElem) == 0)
#endif
	    {

            return (int)i;
	    }
    }

    return List::ELEM_NOT_FOUND;
}


#ifdef AVX
static int
// ListFindElem (List* list, avx_t value)
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
        cmp.m128i = value - list->data[i].elem.m128i; 
///_mm_testz_si128
// == 0 && == 0
        if (cmp.arr[0] + cmp.arr[1] == 0)
	    {
            return (int)i;
	    }
    }
    return List::ELEM_NOT_FOUND;
}
#endif

int 
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

        if (list->data[i].lenElem != Elem::LEN_ELEM_POISON)
        {
            printf ("len = %-2d   ", list->data[i].lenElem);
            printf ("nElem = %-5d ", list->data[i].nElem);

            for (int j = 0; j < list->data[i].lenElem; j++)
            {
#ifdef AVX
                printf ("%c", (list->data[i].elem.str[j]));
#else 
                printf ("%c", (list->data[i].elem[j]));
#endif
            }
        }
        else printf ("pn ");

        printf ("\n");
    }

    printf ("\n");

    return 0;
}

int 
ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= LIST_EXPAND_MULTIPLIER;

    list->data = (List_t*) realloc (list->data/* another ptr  sleva*/, list->capacity * sizeof (List_t));
    if (list->data == nullptr) return 0;

    for (size_t i = list->capacity / LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        // list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].lenElem = Elem::LEN_ELEM_POISON;
        list->data[i].nElem   = Elem::N_ELEM_POISON;
    }

    return 0;
}
