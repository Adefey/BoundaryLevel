#include "IO.h"
#include "stdlib.h"
#include "TypesAndUtils.h"
#include <math.h>
#include <stdio.h>
#include "Functions.h"

struct Params ParseParams(int argc, char **argv)
//Формат запуска: ./Executable M b l T p V0 mu0 rho0 cut_count
{
    struct Params res;
    res.M = atof(argv[1]);
    res.b = atof(argv[2]);
    res.l = atof(argv[3]);
    res.T = atof(argv[4]);
    res.p = atof(argv[5]);
    res.V0 = atof(argv[6]);
    res.mu=atof(argv[7])*pow(res.T/T_norm, m);
    res.rho0=atof(argv[8]);
    res.cut_count=atof(argv[9]);
    res.R=R0/res.M;
    res.rho=res.p/(res.R*res.T);
    //printf("%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%d\n%lf\n%lf\n", res.M, res.b, res.l, res.T, res.p, res.V0, res.mu, res.rho0, res.cut_count, res.R, res.rho);
    return res;
}

void PrintTable1(struct CutInfo *info, struct Params given, int count)
{
    printf("%010s\t%010s\t%010s\t%010s\t%010s\t%010s\t%010s\t%010s\n","x/l", "x", "Re", "delta", "delta**", "delta*", "Cf", "tau");
    for (int i=0; i<count; i++)
    {
        printf("%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\n", info[i].x/given.l, info[i].x, info[i].Rex, info[i].delta, info[i].delta_loss, info[i].delta_dis, info[i].Cf, info[i].tau);
    }
}

void PrintTable2(struct CutInfo *info, struct Params given, struct CutInfo *all_info)
{
    printf("%010s\t%010s\t%010s\t%010s\t%010s\t%010s\t%010s\n","delta", "delta*", "delta**", "H", "tau", "F_summ", "Cf_avg");

        printf("%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\n", info[0].delta, info[0].delta_dis, info[0].delta_loss, info[0].H, info[0].tau, EvaluateForce(all_info, given), EvaluateAvgResistanceFactor(EvaluateForce(all_info, given), given));

        printf("%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\t%010lf\n", info[1].delta, info[1].delta_dis, info[1].delta_loss, info[1].H, info[1].tau, EvaluateForceBlausius(EvaluateAvgResistanceFactorBlausius(info[1]), given), EvaluateAvgResistanceFactorBlausius(info[1]));
}

void PrintTable3(struct CutSpeedInfo **info, struct Params given)
{
    printf("%010s\t%010s\t%010s\t%010s\n", "v_frac", "x", "y", "vxi");
    for (int i=0; i<given.cut_count; i++)
        for (int j=0; j<MAXETACOUNT; j++)
            printf("%010lf\t%010lf\t%010lf\t%010lf\n",info[i][j].v_frac, info[i][j].x, info[i][j].y, info[i][j].vxi);
}

