#include "hashs.h"

static int Hash5Recursion (ELEM_T data, int len);
static int Hash6Recursion (ELEM_T data, int len);
static int MyStrlen (ELEM_T data);

int Hash1 (ELEM_T data)
{
    assert (data);
    return 0;
}

int Hash2 (ELEM_T data)
{
    assert (data);

    if (isupper (data[0])) return (data[0] - 'A') % sizeHashTable;
    if (islower (data[0])) return (data[0] - 'a') % sizeHashTable;

//    if ('A' <= data[0] && data[0] <= 'Z') return (data[0] - 'A') % sizeHashTable;
//    if ('a' <= data[0] && data[0] <= 'z') return (data[0] - 'a') % sizeHashTable;

    return 0;
}

int Hash3 (ELEM_T data)
{
    assert (data);
    return MyStrlen (data) % sizeHashTable;
}

int Hash4 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);
    int sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += (int)(data[0]);
        if (sum >= sizeHashTable) sum %= sizeHashTable;
    }

    return sum;
}

int Hash5 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return Hash5Recursion (data, len) % sizeHashTable;
}

static int Hash5Recursion (ELEM_T data, int len)
{
    assert (data);

    printf ("len = %d\n", len);

    if (len == 1) return (int)(data[0]);

    int hash1 = Hash5Recursion (data, len - 1);

    printf ("hash1 = %d\n", hash1);

    return (hash1 >> 1 | hash1 << (sizeof(int) - 1)) ^ (int)(data[len - 1]);
}

int Hash6 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return Hash6Recursion (data, len) % sizeHashTable;
}

static int Hash6Recursion (ELEM_T data, int len)
{
    assert (data);

    if (len == 1) return (int)(data[0]);

    int hash1 = Hash6Recursion (data, len - 1);

    return (hash1 << 1 | hash1 >> (sizeof(int) - 1)) ^ (int)(data[len - 1]);
}

int Hash7 (ELEM_T data)
{
    assert (data);

    return 0;
}

static int MyStrlen (ELEM_T data)
{
    if (data == nullptr) return 0;
    int i = 0;
    while (data[i] != '\0' &&
           data[i] != '\n' &&
           data[i] != '\t' &&
           data[i] != '\r' &&
           data[i] != ' ') i++;
    return i;
}


