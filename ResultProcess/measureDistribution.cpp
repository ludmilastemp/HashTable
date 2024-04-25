#include "measureDistribution.h"

void DistributionMeasurements (int nHashFunc)
{
    char fileDataName[100] = { 0 };
    sprintf (fileDataName, "Distribution/%s.txt", hashFuncDescription[nHashFunc]);

    char fileResultName[100] = { 0 };
    sprintf (fileResultName, "Distribution/parse_%s.txt", hashFuncDescription[nHashFunc]);

    FILE* fpData = fopen (fileDataName, "r");
    if (fpData == nullptr) return; 

    FILE* fpMeasure = fopen (fileResultName, "w");
    if (fpMeasure == nullptr) 
    {
        fclose (fpData);
        return; 
    }

    long long value = 0;
    long long mean = 0;
    long long variance = 0;

    for (size_t i = 0; i < hashTableSize; i++)
    {
        fscanf (fpData, "%lld", &value);
        mean += value;
    }
    mean /= hashTableSize;
    fprintf (fpMeasure, "mean = %lld\n", mean);
    // printf ("mean = %lld\n", mean);

///////////////////
    fclose (fpData);
    fpData = fopen (fileDataName, "r");
    if (fpData == nullptr) 
    {
        fclose (fpMeasure);
        return; 
    }
///////////////////

    for (size_t i = 0; i < hashTableSize; i++)
    {
        fscanf (fpData, "%lld", &value);
        variance += (value - mean) * (value - mean);
    }

    variance /= hashTableSize;
    fprintf (fpMeasure, "variance = %lld\n"
                        "relative variance = %lld\n", variance, variance / mean);

    fclose (fpData);
    fclose (fpMeasure);
}