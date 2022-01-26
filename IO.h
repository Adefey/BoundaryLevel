#pragma once
#include "TypesAndUtils.h"
//Управление вводом/выводом

struct Params ParseParams(int argc, char **argv);
void PrintTable1(struct CutInfo *info, struct Params given, int count);
void PrintTable2(struct CutInfo *info, struct Params given, struct CutInfo *all_info);
void PrintTable3(struct CutSpeedInfo **info, struct Params given);
