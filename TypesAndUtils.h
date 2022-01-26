#pragma once
//Используемые типы данных - упаковынные характеристики для каждого сечения
#define R0 8.314462618
#define m 0.68
#define T_norm 278
#define MAXETACOUNT 6

struct CutInfo
{
    double x;
    double Rex;
    double delta;
    double delta_loss;
    double delta_dis;
    double H;
    double tau;
    double Cf;
};

struct Params
{
    double M;
    double mu;
    double R;
    double rho;
    double b;
    double l;
    double T;
    double p;
    double V0;
    double rho0;
    int cut_count;
};

struct CutSpeedInfo
{
    double v_frac;
    double x;
    double y;
    double vxi;
};
