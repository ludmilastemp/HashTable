#include "hashs.h"

static unsigned long long Hash5Recursion (ELEM_T data, int len);
static unsigned long long Hash6Recursion (ELEM_T data, int len);
static int MyStrlen (ELEM_T data);

unsigned long long Hash1 (ELEM_T data)
{
    assert (data);
    return 0;
}

unsigned long long Hash2 (ELEM_T data)
{
    assert (data);

    return (unsigned long long)data[0];
}

unsigned long long Hash3 (ELEM_T data)
{
    assert (data);
    return (unsigned long long)MyStrlen (data);
}

unsigned long long Hash4 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);
    unsigned long long sum = 0;

    for (int i = 0; i < len; i++)
    {
        sum += (unsigned long long)(data[i]);
        if (sum >= sizeHashTable) sum %= sizeHashTable;
    }

    return sum;
}

unsigned long long Hash5 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return Hash5Recursion (data, len);
}

static unsigned long long Hash5Recursion (ELEM_T data, int len)
{
    assert (data);

    if (len == 1) return (unsigned long long)(data[0]);

    unsigned long long hash1 = Hash5Recursion (data, len - 1);

    return ((hash1 >> 1) | (hash1 << (sizeof(unsigned long long) - 1))) ^ (unsigned long long)(data[len - 1]);
}

unsigned long long Hash6 (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return Hash6Recursion (data, len) % sizeHashTable;
}

static unsigned long long Hash6Recursion (ELEM_T data, int len)
{
    assert (data);

    if (len == 1) return (unsigned long long)(data[0]);

    unsigned long long hash1 = Hash6Recursion (data, len - 1);

    return ((hash1 << 1) | (hash1 >> (sizeof(unsigned long long) - 1))) ^ (unsigned long long)(data[len - 1]);
}

unsigned long long Hash7 (ELEM_T data)
{
    assert (data);

    return 0;
}

static int MyStrlen (ELEM_T data)
{
    if (data == nullptr) return 0;
    int i = 0;
    while (isalpha(data[i])) i++;

    return i;
}


