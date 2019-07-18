#include "general.h"
#include "interacciones.h"
#include "avanzar.h"
#include "traductor.h"
#include "inicializar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

double velocity_Verlet(double *x,double *v, double *f, int N, double h, double L, double *LUT_F, double *LUT_V, double dr2)
{
	int n=(int)2.5/dr2;
	//armar tabla
	double *tabla_fz_pot;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));
	for (int i=0;i<3*n;i++)
	{*(tabla_fz_pot+3*i)=i*dr2;
	*(tabla_fz_pot+3*i+1)=*(LUT_V+i);
	*(tabla_fz_pot+3*i+2)=*(LUT_F+i);
	}
	/////
	double U;

	U=verlet(x,v,f,L,N, n,tabla_fz_pot,h);

return U;
}

double build_LUTs(int N_LUT, double * LUT_V,double * LUT_F)
{
	int n=N_LUT;
	double *tabla_fz_pot;
	float dr2;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));
	
	dr2=armado_tabla (n, tabla_fz_pot);
	for (int i=0;i<3*n;i++)
	{*(LUT_V+i)=*(tabla_fz_pot+3*i+1);
	*(LUT_F+i)=*(tabla_fz_pot+3*i+2);
	}


return dr2;
}

double inicializar(double *x, double *v,double *f, int N, double L, double T, double *LUT_F, double *LUT_V, double dr2)
{
	int n=(int)2.5/dr2;
	//armar tabla
	double *tabla_fz_pot;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));
	for (int i=0;i<3*n;i++)
	{*(tabla_fz_pot+3*i)=i*dr2;
	*(tabla_fz_pot+3*i+1)=*(LUT_V+i);
	*(tabla_fz_pot+3*i+2)=*(LUT_F+i);
	}
	/////
	
	set_box(x,N,L);
	set_v(v,N,T);
	fuerzas (x, f, L, N, n,tabla_fz_pot);

return 0;
}

