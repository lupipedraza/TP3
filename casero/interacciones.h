#ifndef interacciones_h
#define interacciones_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int armado_tabla (int n, double *tabla_fz_pot);
double interpolar (int n, double r_2, double *tabla_fz_pot, double * F_mod);
double fuerzas (double *x, double *f, float L,  int N,int n,double *tabla_fz_pot);
double presiones (double *x, double *f, float L,  int N,int n, double p,double *tabla_fz_pot);

#endif
