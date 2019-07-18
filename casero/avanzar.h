#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

// Declaracion de funciones

int first_step(double *x, double *v, double *f, int N,float h);
int second_step(double *v, double *f, int N,float h);
int apply_PBC(double *x,float L, int N);
double verlet(double *x, double *v, double *f, float L, int N,int n,	double *tabla_fz_pot, float h);
double energia_k(double *v, int N);
#endif
