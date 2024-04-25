#include <stdio.h>
#include "FileProcess/bufferPreparate.h"
#include "HashTable/hashTable.h"

#include "ResultProcess/plotBuild.h"
#include "ResultProcess/measureProcess.h"
#include "ResultProcess/measureDistribution.h"

int main (const int argc, const char** argv)
{
    if (argc == 1) 
    {
        printf ("Where arguments???\n");
        return 0;
    }

    File file = {};
    BufferPreparate (argv[1], &file);

    FILE* fpMeasurements = nullptr;
    if (measurements)
    {
        char fileMeasurementsName[100] = { 0 };
        sprintf (fileMeasurementsName, "Measurements/%s.txt", &argv[0][2]);

        fpMeasurements = fopen (fileMeasurementsName, "w");
        if (fpMeasurements == nullptr) 
        {
            Fclose (&file);
            return 0; 
        }
    }

    for (int k = 0; k <= nMeasurements * measurements; k++)
    {
        size_t timeBegin = __rdtsc ();

        for (int i = 1; i < argc; i++) 
        {
            int hashFunc = (argv[i][0] - '0' - 1);
            if (0 <= hashFunc && (size_t)hashFunc < sizeof (hashArray) / sizeof (HashFunc_t))
            {

            // printf ("\n\nHashFunc: number = %d %s\n", hashFunc + 1, hashFuncDescription[hashFunc]);

            HashTable hashTable = {};
            HashTableCtor (&hashTable, hashTableSize, hashArray[hashFunc]);

            /**
                * Filling the hash table
                */
            for (size_t j = 0; j < file.nStrings; j++)
            {
                HashTableInsert (&hashTable, &file.buffer[j]);
            }

            // printf ("nWords = %lu\n", hashTable.nUniqueElems);

            // HashTableDump (&hashTable);
            HashTableDumpListsToFile (&hashTable, hashFunc);
            BuildPlotHashTable (hashFunc);
            DistributionMeasurements (hashFunc);

            HashTableDtor (&hashTable);
            }
        }

        size_t timeEnd = __rdtsc ();

        if (measurements)
            fprintf (fpMeasurements, "%lu\n", timeEnd - timeBegin);
    }

    if (measurements)
    {
        fclose (fpMeasurements);
        // ProcessMeasurements (&argv[0][2]);
    }
    
    Fclose (&file);

    printf ("Hello meow!\n");
}
