#include "hashs.h"

#ifdef UNION

static size_t 
MyStrlen (HashData_t data);

Hash_t 
HashReturn0 (HashData_t data)
{
    assert (data.str);

    return 0;
}

Hash_t 
HashLetterASCII (HashData_t data)
{
    assert (data.str);

    return (Hash_t)data.str[0];
}

Hash_t 
HashStrlen (HashData_t data)
{
    assert (data.str);

    return (Hash_t)MyStrlen (data);
}

Hash_t 
HashSumLetterASCII (HashData_t data)
{
    assert (data.str);

    size_t len = MyStrlen (data);
    Hash_t sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (Hash_t)(data.str[i]);
        if (sum >= sizeHashTable) sum %= sizeHashTable;
    }

    return sum;
}

Hash_t 
HashRor (HashData_t data)
{
    assert (data.str);

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)data.str[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash >> 1) | (hash << CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(data.str[i]);
    }

    return hash;
}

Hash_t 
HashRol (HashData_t data)
{
    assert (data.str);

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)data.str[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash << 1) | (hash >> CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(data.str[i]);
    }

    return hash;
}

Hash_t 
Hash7 (HashData_t data)
{
    assert (data.str);

    return 0;
}

static size_t 
MyStrlen (HashData_t data)
{
    assert (data.str);

    size_t i = 0;
    while (data.str[i] != 0) i++;

    return i;
}

#else

static size_t 
MyStrlen (HashData_t data);

Hash_t 
HashReturn0 (HashData_t data)
{
    assert (data);

    return 0;
}

Hash_t 
HashLetterASCII (HashData_t data)
{
    assert (data);

    return (Hash_t)data[0];
}

Hash_t 
HashStrlen (HashData_t data)
{
    assert (data);

    return (Hash_t)MyStrlen (data);
}

Hash_t 
HashSumLetterASCII (HashData_t data)
{
    assert (data);

    size_t len = MyStrlen (data);
    Hash_t sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (Hash_t)(data[i]);
        if (sum >= sizeHashTable) sum %= sizeHashTable;
    }

    return sum;
}

Hash_t 
HashRor (HashData_t data)
{
    assert (data);

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)data[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash >> 1) | (hash << CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(data[i]);
    }

    return hash;
}

Hash_t 
HashRol (HashData_t data)
{
    assert (data);

    size_t len = MyStrlen (data);
    Hash_t hash = (Hash_t)data[0];
    
    for (size_t i = 1; i < len; i++)
    {
        hash = ((hash << 1) | (hash >> CHAR_BIT * (sizeof(Hash_t) - 1))) 
                ^ (Hash_t)(data[i]);
    }

    return hash;
}

Hash_t 
Hash7 (HashData_t data)
{
    assert (data);

    return 0;
}

static size_t 
MyStrlen (HashData_t data)
{
    assert (data);

    size_t i = 0;
    while (data[i] != 0) i++;

    return i;
}

#endif
