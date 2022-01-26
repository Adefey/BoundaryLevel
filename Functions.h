#pragma once
#include "TypesAndUtils.h"
//Реализации математических функций

struct CutInfo EvaluateCutInfo(struct Params given, double length_fraction);
struct CutInfo EvaluateCutInfoBlausius(struct Params given, double length_fraction);
struct CutSpeedInfo EvaluateCutSpeed(struct Params given, struct CutInfo info, double eta);
double EvaluateForce(struct CutInfo *info, struct Params given);
double EvaluateAvgResistanceFactor(double F, struct Params given);
double EvaluateForceBlausius(double Cf, struct Params given);
double EvaluateAvgResistanceFactorBlausius(struct CutInfo info);

