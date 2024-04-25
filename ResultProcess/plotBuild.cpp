#include "plotBuild.h"

void BuildPlotHashTable (int nHashFunc)
{
    char fileDataName[100] = { 0 };
    sprintf (fileDataName, "Distribution/%s.txt", hashFuncDescription[nHashFunc]);

    char fileResultName[100] = { 0 };
    sprintf (fileResultName, "Plot-py/%s.py", hashFuncDescription[nHashFunc]);

    FILE* fpData = fopen (fileDataName, "r");
    if (fpData == nullptr) return; 

    FILE* fpPlot = fopen (fileResultName, "w");
    if (fpPlot == nullptr) 
    {
        fclose (fpData);
        return; 
    }

    size_t listSize = 0;

    fprintf (fpPlot, "import matplotlib.pyplot as plt\n\n"
                 "fig, ax = plt.subplots()\n\n"
                 "numbers = [0");

    for (size_t i = 1; i < hashTableSize; i++)
        fprintf (fpPlot, ", %lu", i);

    fscanf (fpData, "%lu", &listSize);
    fprintf (fpPlot, "]\n"
                 "counts = [%lu", listSize);


    for (size_t i = 1; i < hashTableSize; i++)
    {
        fscanf (fpData, "%lu", &listSize);
        fprintf (fpPlot, ", %lu", listSize);
    }
                 
    fprintf (fpPlot, "]\n\n"
                 "ax.bar(numbers, counts)\n\n"
                 "ax.set_xlabel('номер списка')\n"
                 "ax.set_ylabel('длина списка')\n"
                 "ax.set_title('%s')\n\n"
                 "fig.savefig(\"img/%s.png\")\n"
                //  "plt.show()\n"
                 , hashFuncDescription[nHashFunc], hashFuncDescription[nHashFunc]);

    fclose (fpData);
    fclose (fpPlot);
}