#ifndef interacciones_h
#define interacciones_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int armado_tabla (int n, double *tabla_fz_pot);
double interpolar (double r_2, double *tabla_fz_pot, double *fz_u_nuevas);

#endif
