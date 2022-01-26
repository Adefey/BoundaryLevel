#include <stdio.h>
#include "TypesAndUtils.h"
#include "Functions.h"
#include "IO.h"
#include <stdlib.h>

struct CutInfo *EvaluateTable1(struct Params given);
struct CutInfo *EvaluateTable2(struct Params given);
struct CutSpeedInfo **EvaluateTable3(struct Params given, struct CutInfo *info);

int main(int argc, char **argv)
{
    struct Params given = ParseParams(argc, argv);

    printf("%s\n", "Table 1");
    struct CutInfo *cutinfo = EvaluateTable1(given);
    PrintTable1(cutinfo, given, given.cut_count);

    printf("%s\n", "Table 2");
    struct CutInfo *cutblausius = EvaluateTable2(given);
    PrintTable2(cutblausius, given, cutinfo);
    free(cutblausius);

    printf("%s\n", "Table 3");
    struct CutSpeedInfo **speed = EvaluateTable3(given, cutinfo);
    PrintTable3(speed, given);

    free(cutinfo);
    for (int i=0; i<MAXETACOUNT; i++)
        free(speed[i]);
    free(speed);
    return 0;
}

struct CutInfo *EvaluateTable1(struct Params given)
{
    struct CutInfo *res = (struct CutInfo*)malloc(sizeof(struct CutInfo) * given.cut_count);
    for (double i=0; i<given.cut_count; i++)
    {
        res[(int)i] = EvaluateCutInfo(given, (i+1.0)/given.cut_count);
    }
    return res;
}

struct CutInfo *EvaluateTable2(struct Params given)
{
    struct CutInfo *res = (struct CutInfo*)malloc(sizeof(struct CutInfo) * 2);
    res[0] = EvaluateCutInfo(given, 1.0);
    res[1] = EvaluateCutInfoBlausius(given, 1.0);
    return res;
}

struct CutSpeedInfo **EvaluateTable3(struct Params given, struct CutInfo *info)
{
    struct CutSpeedInfo **res = (struct CutSpeedInfo**)malloc(sizeof(struct CutSpeedInfo*)*given.cut_count);
    for (int i=0; i<given.cut_count; i++)
    {
        res[i] = (struct CutSpeedInfo*)malloc(sizeof(struct CutSpeedInfo) * MAXETACOUNT);
        for (int j=0; j<6; j++)
        {
            if (j!=5)
                res[i][j] = EvaluateCutSpeed(given, info[i], ((double)j/(MAXETACOUNT-1)));
            else
                res[i][j] = EvaluateCutSpeed(given, info[i], (((double)j-0.1)/(MAXETACOUNT-1)));
        }
    }
    return res;
}
