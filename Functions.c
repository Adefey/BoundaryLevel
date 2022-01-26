#include "TypesAndUtils.h"
#include "Functions.h"
#include <math.h>
#include <stdio.h>

struct CutInfo EvaluateCutInfo(struct Params given, double length_fraction)
{
    struct CutInfo res;
    res.x = given.l*length_fraction;
    res.Rex=given.rho*given.V0*res.x/given.mu;
    res.delta_loss=sqrt(0.4698/res.Rex)*res.x;
    res.delta=res.delta_loss*315.0/37.0;
    res.delta_dis=res.delta*3.0/10.0;
    res.H=res.delta_dis/res.delta_loss;
    res.tau=2.0*given.mu*given.V0/res.delta;
    res.Cf = 2.0*res.tau/(given.rho*pow(given.V0, 2.0));
    return res;
}

struct CutInfo EvaluateCutInfoBlausius(struct Params given, double length_fraction)
{
    struct CutInfo res;
    res.x=given.l*length_fraction;
    res.Rex=given.rho*given.V0*res.x/given.mu;
    res.delta=0.99/sqrt(res.Rex)*given.l;
    res.delta_dis=1.729/sqrt(res.Rex)*given.l;
    res.delta_loss=0.664/sqrt(res.Rex)*given.l;
    res.H=res.delta_dis/res.delta_loss;
    res.tau=0.332*given.mu*given.V0/given.l*sqrt(res.Rex);
    res.Cf=0.664/sqrt(res.Rex);
    return res;
}

struct CutSpeedInfo EvaluateCutSpeed(struct Params given, struct CutInfo info, double eta)
{
    struct CutSpeedInfo res;
    res.v_frac =2.0*eta-2.0*pow(eta, 3.0)+pow(eta, 4.0);
    res.x = info.x;
    res.y=eta/sqrt(info.Rex)*res.x;
    res.vxi = res.v_frac*given.V0;
    return res;
}

double EvaluateForce(struct CutInfo *info, struct Params given)
{
    double res=0;
    for (int i=0; i<given.cut_count; i++)
        res+=info[i].tau*given.l/given.cut_count;
    return res*given.b;
}

double EvaluateAvgResistanceFactor(double F, struct Params given)
{
    return (2.0*F)/(given.rho0*pow(given.V0, 2.0)/2.0*given.b*given.l);
}

double EvaluateForceBlausius(double Cf, struct Params given)
{
    return Cf*given.rho0*pow(given.V0, 2.0)/2.0*given.b*given.l;
}

double EvaluateAvgResistanceFactorBlausius(struct CutInfo info)
{
    return 0.644/sqrt(info.Rex);
}
