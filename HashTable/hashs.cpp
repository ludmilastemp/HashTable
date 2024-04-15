#include "hashs.h"

static unsigned long long HashRorRecursion (ELEM_T data, int len);
static unsigned long long HashRolRecursion (ELEM_T data, int len);
static int MyStrlen (ELEM_T data);

unsigned long long HashReturn0 (ELEM_T data)
{
    assert (data);
    return 0;
}

unsigned long long HashLetterASCII (ELEM_T data)
{
    assert (data);

    return (unsigned long long)data[0];
}

unsigned long long HashStrlen (ELEM_T data)
{
    assert (data);
    return (unsigned long long)MyStrlen (data);
}

unsigned long long HashSumLetterASCII (ELEM_T data)
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

unsigned long long HashRor (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return HashRorRecursion (data, len);
}

static unsigned long long HashRorRecursion (ELEM_T data, int len)
{
    assert (data);

    if (len == 1) return (unsigned long long)(data[0]);

    unsigned long long hash = HashRorRecursion (data, len - 1);

    return ((hash >> 1) | (hash << (sizeof(unsigned long long) - 1))) ^ (unsigned long long)(data[len - 1]);
}

unsigned long long HashRol (ELEM_T data)
{
    assert (data);

    int len = MyStrlen (data);

    return HashRolRecursion (data, len) % sizeHashTable;
}

static unsigned long long HashRolRecursion (ELEM_T data, int len)
{
    assert (data);

    if (len == 1) return (unsigned long long)(data[0]);

    unsigned long long hash = HashRolRecursion (data, len - 1);

    return ((hash << 1) | (hash >> (sizeof(unsigned long long) - 1))) ^ (unsigned long long)(data[len - 1]);
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
    while (data[i] != 0) i++;

    return i;
}


