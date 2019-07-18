#include "general.h"
#include "inicializar.h"
#include "avanzar.h"
#include "visualizacion.h"
#include "interacciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
	srand(time(NULL));

	int n=100000; //es para el refinamiento de las tablas
	int N= 512;//512; //numero de particulas
	//para que rho=N/L^3 =0.8442 -> L=8.4646
	float L=8.4646;
	float T=0.728;

	char filename1[255];
 	sprintf(filename1, "T=%lf_N=%d.lammpstrj",T,N); //

	FILE *fp;
	char filename[64];
 	sprintf(filename, "ej1_%d_%lf.txt",N,T);
	fp= fopen(filename,	"a");
/*
	FILE *fp2;
	char filename2[64];
 	sprintf(filename2, "presiones.txt");
	fp2= fopen(filename2,	"a");
*/

	double *tabla_fz_pot;
	tabla_fz_pot=(double *)malloc(3*n*sizeof(double));

	double *f;
	f=(double *)malloc(N*3*sizeof(double));
	//seteo en 0 las fuerzas
	for(int k=0;k<3*N;k++)
	{
	*(f+k)=0;
	}

	double h=0.001;
	armado_tabla(n,tabla_fz_pot);

	double *x;
	x=(double *)malloc(3*N*sizeof(double));
	double *v;
	v=(double *)malloc(3*N*sizeof(double));



	set_box(x,N,L);
	set_v(v,N,T);

	save_lammpstrj(filename1, x, v, N, L, 0);

	double u_n;
	double e_c;
	double temps;
//	double ro = N/(L*L*L);
//	double p=ro*N*T;
//	double u_t=0; //energia total por numero de particula

	for (int i=0;i<7000;i++)
	{

		u_n=verlet(x,v,f,L,N, n,tabla_fz_pot,h);


		save_lammpstrj(filename1, x, v, N, L, i);
		//u_t+=u_n;

		e_c= energia_k(v,N);

		temps= (double) (2*e_c)/(3*N);

		fprintf(fp,"%lf ", temps);
		fprintf(fp,"%lf ", e_c);
		fprintf(fp,"%lf \n", u_n);

/*
	for (int k=1;k<100;k++)
		{u_n=verlet(x,v,f,L,N, n,tabla_fz_pot,h);
		printf("%lf  \n",u_n);
		save_lammpstrj(filename, x, v, N, L, i);  // La guardo (append para 0<l)
		p+=presiones(x, f, L, N, n, p)/(3*L*L*L);
		u_t+=u_n;
		e_c= energia_k(v,N);
		temps= (double) (2*e_c)/(3);
	} */




//	fprintf(fp3,"%lf ", p);

	}
	fclose(fp);
//	fclose(fp3);

	//free(v);
	//free(x);
return 0;
}
