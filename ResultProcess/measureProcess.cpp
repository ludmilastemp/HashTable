#include "measureProcess.h"

void ProcessMeasurements (const char* const realize)
{
    assert (realize);

    char fileDataName[100] = { 0 };
    sprintf (fileDataName, "Measurements/%s.txt", realize);

    char fileResultName[100] = { 0 };
    sprintf (fileResultName, "Measurements/parse_%s.txt", realize);

    FILE* fpData = fopen (fileDataName, "r");
    if (fpData == nullptr) return; 

    FILE* fpMeasure = fopen (fileResultName, "w");
    if (fpMeasure == nullptr) 
    {
        fclose (fpData);
        return; 
    }

    long long time = 0;
    long long meanTime = 0;
    long long variance = 0;

    for (size_t i = 0; i < nMeasurements; i++)
    {
        fscanf (fpData, "%lld", &time);
        meanTime += time;
    }
    meanTime /= nMeasurements;
    fprintf (fpMeasure, "mean time = %lld\n", meanTime);
    printf ("mean time = %lld\n", meanTime / 1000000);

///////////////////
    fclose (fpData);
    fpData = fopen (fileDataName, "r");
    if (fpData == nullptr) 
    {
        fclose (fpMeasure);
        return; 
    }
///////////////////

    for (size_t i = 0; i < nMeasurements; i++)
    {
        fscanf (fpData, "%lld", &time);
        variance += (time - meanTime) * (time - meanTime);
    }

    variance /= nMeasurements;
    fprintf (fpMeasure, "variance = %lld\n"
                        "relative variance = %lld\n", variance, variance / meanTime);

    // printf ("variance = %lld\n"
    //         "relative variance = %lld\n", variance, variance / meanTime);

    fclose (fpData);
    fclose (fpMeasure);
}