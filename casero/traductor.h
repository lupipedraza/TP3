#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

double velocity_Verlet(double *x,double *v, double *f, int N, double h, double *LUT_F, double *LUT_V, double drc);
double build_LUTs(int N_LUT, double * LUT_V,double * LUT_F);
double inicializar(double *x, double *v,double *f, int N, double L, double T, double *LUT_F, double *LUT_V, double dr2);
#endif
