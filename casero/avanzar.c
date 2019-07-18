#include "general.h"
#include "interacciones.h"
#include "avanzar.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Definicion de funciones

int first_step(double *x, double *v, double *f, int N,float h)
{	double m=1.0;
	for( int j=0;j<N;j++)
		{for(int k=0;k<3;k++)
			{/* printf("%d \n", j);*/
				*(x+(3*j)+k)=*(x+(3*j)+k)+*(v+(3*j)+k)*h+ (*(f+(3*j)+k)*h*h)/(2*m);
				*(v+(3*j)+k)=*(v+(3*j)+k)+(*(f+(3*j)+k)*h)/(2*m);//en realidad es v(t+h/2)
			}
		}
	return 0;
}

int second_step(double *v, double *f, int N,float h)
{
	double m=1.0;
	for( int j=0;j<N;j++)
		{for(int k=0;k<3;k++)
			{	/*printf("%d \n", j);*/
				*(v+(3*j)+k)=*(v+(3*j)+k)+(*(f+(3*j)+k)*h)/(2*m);}//en realidad es v(t+h/2)
		}
	return 0;
}

int apply_PBC(double *x,float L, int N)
{
	for( int j=0;j<N;j++)
	{ for(int k=0;k<3;k++)
			{/*printf("%d \n", j);*/
				if(*(x+(3*j)+k)<0.0){
				*(x+(3*j)+k)+=L;}
				if(*(x+(3*j)+k)>L){
				*(x+(3*j)+k)-=L;}
			}
	}
	return 0;
}



double verlet(double *x, double *v, double *f, float L, int N,int n,	double *tabla_fz_pot, float h)
{
	double U_n=0;
	first_step(x, v, f, N,h);
	apply_PBC(x,L,N);
	U_n=fuerzas (x, f, L, N, n,tabla_fz_pot);

	second_step(v, f, N,h);
	return U_n;

}


double energia_k(double *v, int N)
{
	double e_c=0;

	for( int j=0;j<N;j++)
	{ for(int k=0;k<3;k++)
			{/*printf("%d \n", j);*/
			e_c+=(*(v+(3*j)+k) * (*(v+(3*j)+k)))/2;
			}
	}
	return e_c;
}
