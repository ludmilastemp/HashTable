#include "list.h"

List*
ListStructCtor ()
{
    List* list = (List*) calloc (1, sizeof (List));
    assert (list);

    list->capacity = LIST_INITIAL_CAPACITY;

    ListStructRealloc (list);

    list->size = LIST_INITIAL_SIZE;

    for (int i = 0; i < LIST_INITIAL_CAPACITY; ++i)
    {
        list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].lenElem = Elem::LEN_ELEM_POISON;
        list->data[i].nElem   = Elem::N_ELEM_POISON;
    }

    return list;
}

int ListStructDtor (List* list)
{
    if (list == nullptr) return 0;

    free (list->data);
    list->data     = nullptr;
    list->capacity = 0;
    list->size     = 0;

    free (list);

    return 0;
}

int
ListInsert (List* list, LIST_T value)
{
    assert (list);

    if (list->size >= list->capacity - 1) ListStructRealloc (list);

    list->data[list->size] = value;
    list->size++;

    return list->size - 1;
}

int
ListFindElem (List* list, ELEM_T value, int lenElem)
{
    assert (list);

    for (int i = 0; i < list->size; i++)
    {
        if (list->data[i].lenElem == lenElem &&
            strncmp (value, list->data[i].elem, (size_t)lenElem) == 0)
            return i;
    }
    return List::ELEM_NOT_FOUND;
}

int ListStructDump (List* list)
{
    assert (list);

    printf ("LIST %p\n", list);
    printf ("capacity = %d\n", list->capacity);
    printf ("size = %d\n", list->size);

    printf ("\n\n");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf ("%-3d ", i);

        if (list->data[i].elem != Elem::DATA_POISON)
        {
            printf ("len = %-2d   ", list->data[i].lenElem);
            printf ("nElem = %-5d ", list->data[i].nElem);

            for (int j = 0; j < list->data[i].lenElem; j++)
            {
                printf ("%c", (list->data[i].elem[j]));
            }
        }
        else printf ("pn ");

        printf ("\n");
    }

    printf ("\n");

    return 0;
}

#define ERROR(x) printf ("ERROR!!! " #x "\n")

int ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= LIST_EXPAND_MULTIPLIER;

    list->data = (LIST_T*) realloc (list->data, (size_t)list->capacity * sizeof (LIST_T));
    if (list->data == nullptr) ERROR (DATA_NULLPTR);
    assert (list->data);

    for (int i = list->capacity / LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        list->data[i].elem    = Elem::DATA_POISON;
        list->data[i].lenElem = Elem::LEN_ELEM_POISON;
        list->data[i].nElem   = Elem::N_ELEM_POISON;
    }

    return 0;
}
