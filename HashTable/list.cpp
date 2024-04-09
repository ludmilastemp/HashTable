#include "list.h"

List*
ListStructCtor ()
{
    List* list = (List*) calloc (1, sizeof (List));
    assert (list);

    list->capacity = LIST_INITIAL_CAPACITY;

    ListStructRealloc (list);

    list->size = LIST_INITIAL_SIZE;
    list->free = 1;

    for (int i = 0; i < list->capacity; ++i)
    {
        *(list->data + i) = List::DATA_POISON;
        *(list->prev + i) = List::PREV_POISON;
        *(list->next + i) = i + 1;
    }

    list->next[0] = 0;
    list->prev[0] = 0;
    list->next[list->capacity - 1] = 0;

    return list;
}

int ListStructDtor (List* list)
{
    free (list->data);
    free (list->next);
    free (list->prev);

    list->data = nullptr;
    list->next = nullptr;
    list->prev = nullptr;

    list->capacity = 0;
    list->size = 0;
    list->free = 0;

    free (list);

    return 0;
}

int
ListInsert (List* list, int index, LIST_T value)
{
    if (list->size > list->capacity - 4)           /// - ?
                                  /** 4 = head + free + cycle + tmp */
                                  // in ListStructRealloc
                                  // maybe check capacity == 0
    {
        ListStructRealloc (list);
    }

    int insertIndex = list->free;
    list->free  = list->next[insertIndex];

    list->data[insertIndex] = value;

    list->prev[insertIndex] = list->prev[list->next[index]];
    list->prev[list->next[index]] = insertIndex;

    list->next[insertIndex] = list->next[index];
    list->next[index] = insertIndex;

    list->size++;

    return insertIndex;
}

int
ListFindInNElem (List* list, int initialIndex, int nElem, ELEM_T value, int lenElem)
{
    assert (list);

    int index = initialIndex;
    for (int i = 0; i < nElem; i++)
    {
        if (list->data[index].lenElem == lenElem &&
            strncmp (value, list->data[index].elem, (size_t)lenElem) == 0)
            return index;

        index = list->next[index];
    }
    return -1;
}

#define ERROR(x) printf ("ERROR!!! " #x "\n")

int ListStructVerificator (List* list)
{
    if (list->capacity <= 0)
    {
        ERROR (INCORRECT_CAPACITY);
        return 1;
    }

    if (list->size < 0) ERROR (INCORRECT_SIZE);
    if (list->free < 0) ERROR (INCORRECT_FREE);

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->next[i] >= list->capacity || list->next[i] < -1)
            ERROR (INCORRECT_NEXT_DATA);

        if (list->prev[i] >= list->capacity || list->prev[i] < -1)
            ERROR (INCORRECT_PREV_DATA);
    }

    int index = list->next[0];
    for (int i = 0; i < list->size; i++)
    {
        if (list->prev[index] == List::PREV_POISON) ERROR (INCORRECT_PREV_DATA);

        index = list->next[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    index = list->free;
    for (int i = 0; i < list->capacity - list->size - 1; i++)
    {
        if (list->prev[index] != List::PREV_POISON) ERROR (INCORRECT_PREV_DATA);

        index = list->next[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    index = list->prev[0];
    for (int i = 0; i < list->size; i++)
    {
        if (index == -1) ERROR (INCORRECT_PREV_DATA);

        index = list->prev[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    return 0;
}

#undef ERROR

int ListStructDump (List* list)
{
    printf ("LIST %p\n", list);
    printf ("capacity = %d\n", list->capacity);
    printf ("size = %d\n", list->size);
    printf ("free = %d\n", list->free);

    printf ("\n\n");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf ("%c %3d ", i + 'a' - 1, i);
        printf ("next %3d ", list->next[i]);
        printf ("prev %3d ", list->prev[i]);

        if (list->data[i].lenElem != List::DATA_POISON.lenElem)
            printf ("len %2d ", list->data[i].lenElem);
        else printf ("len pn ");

        if (list->data[i].nElem != List::DATA_POISON.nElem)
            printf ("nElem %2d ", list->data[i].nElem);
        else printf ("nElem pn ");

        if (list->data[i].elem != List::DATA_POISON.elem)
        for (int j = 0; j < list->data[i].lenElem; j++)
            printf ("%c", *(list->data[i].elem + j));
        else printf ("pn ");

        printf ("\n\n");
    }

    printf ("\n");

    return 0;
}

#define ERROR(x) printf ("ERROR!!! " #x "\n")

int ListStructRealloc (List *list)
{
    assert (list);

    list->capacity--;
    list->capacity *= LIST_EXPAND_MULTIPLIER;

    list->data = (LIST_T*) realloc (list->data, (size_t)list->capacity * sizeof (LIST_T));
    if (list->data == nullptr) ERROR (DATA_NULLPTR);
    assert (list->data);

    list->next = (int*) realloc (list->next, (size_t)list->capacity * sizeof (int));
    if (list->next == nullptr) ERROR (NEXT_NULLPTR);
    assert (list->next);

    list->prev = (int*) realloc (list->prev, (size_t)list->capacity * sizeof (int));
    if (list->prev == nullptr) ERROR (PREV_NULLPTR);
    assert (list->prev);

    for (int i = list->capacity / LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        *(list->data + i) = List::DATA_POISON;
        *(list->prev + i) = List::PREV_POISON;
        *(list->next + i) = i + 1;
    }

    list->next[list->capacity - 1] = list->free;
    list->free = list->capacity / LIST_EXPAND_MULTIPLIER;

    return 0;
}
