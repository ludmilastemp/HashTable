#include "hashs.h"

static size_t 
MyStrlen (HashData_t* data);

Hash_t 
HashReturn0 (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    return 0;
}

Hash_t 
HashLetterASCII (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    return (Hash_t)GetElemCharPtr (data)[0];
}

Hash_t 
HashStrlen (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    return (Hash_t)MyStrlen (data);
}

Hash_t 
HashSumLetterASCII (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    size_t len = MyStrlen (data);
    Hash_t sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (Hash_t)(GetElemCharPtr (data)[i]);
        if (sum >= sizeHashTable) sum %= sizeHashTable;
    }

    return sum;
}

Hash_t 
HashRor (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)GetElemCharPtr (data)[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash >> 1) | (hash << CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(GetElemCharPtr (data)[i]);
    }

    return hash;
}

Hash_t 
HashRol (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)GetElemCharPtr (data)[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash << 1) | (hash >> CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(GetElemCharPtr (data)[i]);
    }

    return hash;
}

Hash_t 
Hash7 (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    return 0;
}

static size_t 
MyStrlen (HashData_t* data)
{
    assert (GetElemCharPtr (data));

    size_t i = 0;
    while (GetElemCharPtr (data)[i] != 0) i++;

    return i;
}
